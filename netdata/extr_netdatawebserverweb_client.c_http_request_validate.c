#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct web_client {size_t header_parse_last_size; int header_parse_tries; scalar_t__ mode; int /*<<< orphan*/  decoded_url; int /*<<< orphan*/  last_url; TYPE_1__ response; } ;
typedef  int /*<<< orphan*/  HTTP_VALIDATION ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_VALIDATION_INCOMPLETE ; 
 int /*<<< orphan*/  HTTP_VALIDATION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  HTTP_VALIDATION_OK ; 
 scalar_t__ NETDATA_WEB_REQUEST_URL_SIZE ; 
 scalar_t__ WEB_CLIENT_MODE_NORMAL ; 
 scalar_t__ WEB_CLIENT_MODE_OPTIONS ; 
 scalar_t__ WEB_CLIENT_MODE_STREAM ; 
 size_t buffer_strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_tostring (int /*<<< orphan*/ ) ; 
 char* http_header_parse (struct web_client*,char*,int) ; 
 int /*<<< orphan*/  info (char*,int,size_t) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  url_decode_r (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  web_client_disable_wait_receive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_wait_receive (struct web_client*) ; 

__attribute__((used)) static inline HTTP_VALIDATION http_request_validate(struct web_client *w) {
    char *s = (char *)buffer_tostring(w->response.data), *encoded_url = NULL;

    size_t last_pos = w->header_parse_last_size;
    if(last_pos > 4) last_pos -= 4; // allow searching for \r\n\r\n
    else last_pos = 0;

    w->header_parse_tries++;
    w->header_parse_last_size = buffer_strlen(w->response.data);

    if(w->header_parse_tries > 1) {
        if(w->header_parse_last_size < last_pos)
            last_pos = 0;

        if(strstr(&s[last_pos], "\r\n\r\n") == NULL) {
            if(w->header_parse_tries > 10) {
                info("Disabling slow client after %zu attempts to read the request (%zu bytes received)", w->header_parse_tries, buffer_strlen(w->response.data));
                w->header_parse_tries = 0;
                w->header_parse_last_size = 0;
                web_client_disable_wait_receive(w);
                return HTTP_VALIDATION_NOT_SUPPORTED;
            }

            return HTTP_VALIDATION_INCOMPLETE;
        }
    }

    // is is a valid request?
    if(!strncmp(s, "GET ", 4)) {
        encoded_url = s = &s[4];
        w->mode = WEB_CLIENT_MODE_NORMAL;
    }
    else if(!strncmp(s, "OPTIONS ", 8)) {
        encoded_url = s = &s[8];
        w->mode = WEB_CLIENT_MODE_OPTIONS;
    }
    else if(!strncmp(s, "STREAM ", 7)) {
        encoded_url = s = &s[7];
        w->mode = WEB_CLIENT_MODE_STREAM;
    }
    else {
        w->header_parse_tries = 0;
        w->header_parse_last_size = 0;
        web_client_disable_wait_receive(w);
        return HTTP_VALIDATION_NOT_SUPPORTED;
    }

    // find the SPACE + "HTTP/"
    while(*s) {
        // find the next space
        while (*s && *s != ' ') s++;

        // is it SPACE + "HTTP/" ?
        if(*s && !strncmp(s, " HTTP/", 6)) break;
        else s++;
    }

    // incomplete requests
    if(unlikely(!*s)) {
        web_client_enable_wait_receive(w);
        return HTTP_VALIDATION_INCOMPLETE;
    }

    // we have the end of encoded_url - remember it
    char *ue = s;

    // make sure we have complete request
    // complete requests contain: \r\n\r\n
    while(*s) {
        // find a line feed
        while(*s && *s++ != '\r');

        // did we reach the end?
        if(unlikely(!*s)) break;

        // is it \r\n ?
        if(likely(*s++ == '\n')) {

            // is it again \r\n ? (header end)
            if(unlikely(*s == '\r' && s[1] == '\n')) {
                // a valid complete HTTP request found

                *ue = '\0';
                url_decode_r(w->decoded_url, encoded_url, NETDATA_WEB_REQUEST_URL_SIZE + 1);
                *ue = ' ';
                
                // copy the URL - we are going to overwrite parts of it
                // TODO -- ideally we we should avoid copying buffers around
                strncpyz(w->last_url, w->decoded_url, NETDATA_WEB_REQUEST_URL_SIZE);

                w->header_parse_tries = 0;
                w->header_parse_last_size = 0;
                web_client_disable_wait_receive(w);
                return HTTP_VALIDATION_OK;
            }

            // another header line
            s = http_header_parse(w, s,
                    (w->mode == WEB_CLIENT_MODE_STREAM) // parse user agent
            );
        }
    }

    // incomplete request
    web_client_enable_wait_receive(w);
    return HTTP_VALIDATION_INCOMPLETE;
}