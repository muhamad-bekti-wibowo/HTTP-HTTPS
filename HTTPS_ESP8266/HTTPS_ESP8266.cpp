/*
  06 Juni 2024 developed by Muhammad Bekti Wibowo

  Program ini dikembangkan oleh Muhammad Muhammad Bekti Wibowo untuk pengembangan project dengan HTTPS.
  khususnya untuk project saya di https://
  Dukung saya untuk membeli server di https://saweria.co/FastProjectMBW

  Program Sebelumnya Dibuat Oleh Rui Santos
  Lengkapi detail proyek di Lengkapi detail proyek di https://RandomNerdTutorials.com/
  Izin dengan ini diberikan, tanpa biaya, kepada siapa pun yang mendapatkan salinan perangkat lunak ini dan file dokumentasi terkait.
  Pemberitahuan hak cipta di atas dan pemberitahuan izin ini harus menyertakan semua salinan atau sebagian besar dari Perangkat Lunak.

  Referensi
  ~ https://randomnerdtutorials.com/esp8266-nodemcu-https-requests/
  ~ https://randomnerdtutorials.com/esp32-https-requests/
  ~ https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/
  ~ https://www.geeksforgeeks.org/http-headers-content-type/
  ~ https://circuits4you.com/2019/02/08/esp8266-nodemcu-https-secured-post-request/

  This program was developed by Muhammad Bekti Wibowo for project development with HTTPS.
  especially for my project at https://
  Support me to buy server at https://saweria.co/FastProjectMBW

  Previous Program Created By Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/
  Permission is hereby granted, without charge, to anyone who obtains a copy of this software and associated documentation files.
  The above copyright notice and this permission notice must include all copies or a large portion of the Software.

  Reference
  ~ https://randomnerdtutorials.com/esp8266-nodemcu-https-requests/
  ~ https://randomnerdtutorials.com/esp32-https-requests/
  ~ https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/
  ~ https://www.geeksforgeeks.org/http-headers-content-type/
  ~ https://circuits4you.com/2019/02/08/esp8266-nodemcu-https-secured-post-request/
*/
#include "HTTPS_ESP8266.h"

WiFiClientSecure client;
HTTPS_ESP8266::HTTPS_ESP8266(String _linkpost, String _linkget, String _Link)
{
    linkget = _linkget;
    linkpost = _linkpost;
    Link = _Link;
}
String HTTPS_ESP8266::HTTPS_GET(String data)
{
    client.setInsecure();
    HTTPClient https;
    if (https.begin(client, "https://" + linkget))
    {
        int httpCode = https.GET();
        if (httpCode > 0)
        {
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = https.getString();
                payload.trim();
                https.end();
                return payload;
            }
            return String(httpCode);
        }
        else
        {
            https.end();
            return "[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str();
        }
        return "2";
    }
    return "3";
}
String HTTPS_ESP8266::HTTPS_POST(String data)
{
    client.setInsecure();
    if (client.connect(Link.c_str(), 443))
    {
        client.print(String("POST ") + linkpost + " HTTP/1.1\r\n" +
                     "Host: " + Link + "\r\n" +
                     "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                     "Content-Length: " + "" + String(data.length()) + "" + "\r\n\r\n" +
                     "" + data + "\r\n\r\n" +
                     "Connection: close\r\n\r\n");

        client.readStringUntil('H');
        String Reply = "H";
        while (client.available())
        {
            char c = client.read();
            Reply += String(c);
        }
        client.stop();
        // Reply = (Reply.substring(Reply.indexOf("\r\n\r\n"), Reply.indexOf("\n\n\n")));
        // Reply.trim();
        return Reply;
    }
    return "";
}