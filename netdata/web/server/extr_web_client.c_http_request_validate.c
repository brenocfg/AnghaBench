#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; scalar_t__ conn; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct web_client {size_t header_parse_last_size; int header_parse_tries; int* url_search_path; scalar_t__ mode; int separator; int url_path_length; TYPE_2__ ssl; int /*<<< orphan*/  decoded_url; int /*<<< orphan*/  last_url; int /*<<< orphan*/  decoded_query_string; TYPE_1__ response; } ;
typedef  int /*<<< orphan*/  HTTP_VALIDATION ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_VALIDATION_INCOMPLETE ; 
 int /*<<< orphan*/  HTTP_VALIDATION_MALFORMED_URL ; 
 int /*<<< orphan*/  HTTP_VALIDATION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  HTTP_VALIDATION_OK ; 
 int /*<<< orphan*/  HTTP_VALIDATION_REDIRECT ; 
 int NETDATA_SSL_NO_HANDSHAKE ; 
 scalar_t__ NETDATA_WEB_REQUEST_URL_SIZE ; 
 scalar_t__ WEB_CLIENT_MODE_NORMAL ; 
 scalar_t__ WEB_CLIENT_MODE_STREAM ; 
 int WEB_FIELDS_MAX ; 
 size_t buffer_strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_tostring (int /*<<< orphan*/ ) ; 
 char* http_header_parse (struct web_client*,char*,int) ; 
 int /*<<< orphan*/  info (char*,int,size_t) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ netdata_srv_ctx ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  url_decode_r (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* url_find_protocol (char*) ; 
 int url_is_request_complete (char*,char*,size_t) ; 
 int url_map_query_string (char**,char*) ; 
 scalar_t__ url_parse_query_string (int /*<<< orphan*/ ,scalar_t__,char**,int) ; 
 int /*<<< orphan*/  web_client_check_unix (struct web_client*) ; 
 int /*<<< orphan*/  web_client_disable_wait_receive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_wait_receive (struct web_client*) ; 
 scalar_t__ web_client_is_using_ssl_default (struct web_client*) ; 
 scalar_t__ web_client_is_using_ssl_force (struct web_client*) ; 
 int /*<<< orphan*/  web_client_split_path_query (struct web_client*,char*) ; 
 char* web_client_valid_method (struct web_client*,char*) ; 

__attribute__((used)) static inline HTTP_VALIDATION http_request_validate(struct web_client *w) {
    char *s = (char *)buffer_tostring(w->response.data), *encoded_url = NULL;

    size_t last_pos = w->header_parse_last_size;

    w->header_parse_tries++;
    w->header_parse_last_size = buffer_strlen(w->response.data);

    int is_it_valid;
    if(w->header_parse_tries > 1) {
        if(last_pos > 4) last_pos -= 4; // allow searching for \r\n\r\n
        else last_pos = 0;

        if(w->header_parse_last_size < last_pos)
            last_pos = 0;

        is_it_valid = url_is_request_complete(s, &s[last_pos], w->header_parse_last_size);
        if(!is_it_valid) {
            if(w->header_parse_tries > 10) {
                info("Disabling slow client after %zu attempts to read the request (%zu bytes received)", w->header_parse_tries, buffer_strlen(w->response.data));
                w->header_parse_tries = 0;
                w->header_parse_last_size = 0;
                web_client_disable_wait_receive(w);
                return HTTP_VALIDATION_NOT_SUPPORTED;
            }

            return HTTP_VALIDATION_INCOMPLETE;
        }

        is_it_valid = 1;
    } else {
        last_pos = w->header_parse_last_size;
        is_it_valid = url_is_request_complete(s, &s[last_pos], w->header_parse_last_size);
    }

    s = web_client_valid_method(w, s);
    if (!s) {
        w->header_parse_tries = 0;
        w->header_parse_last_size = 0;
        web_client_disable_wait_receive(w);

        return HTTP_VALIDATION_NOT_SUPPORTED;
    } else if (!is_it_valid) {
        //Invalid request, we have more data after the end of message
        char *check = strstr((char *)buffer_tostring(w->response.data), "\r\n\r\n");
        if(check) {
            check += 4;
            if (*check) {
                w->header_parse_tries = 0;
                w->header_parse_last_size = 0;
                web_client_disable_wait_receive(w);
                return HTTP_VALIDATION_NOT_SUPPORTED;
            }
        }

        web_client_enable_wait_receive(w);
        return HTTP_VALIDATION_INCOMPLETE;
    }

    //After the method we have the path and query string together
    encoded_url = s;

    //we search for the position where we have " HTTP/", because it finishes the user request
    s = url_find_protocol(s);

    // incomplete requests
    if(unlikely(!*s)) {
        web_client_enable_wait_receive(w);
        return HTTP_VALIDATION_INCOMPLETE;
    }

    // we have the end of encoded_url - remember it
    char *ue = s;

    //Variables used to map the variables in the query string case it is present
    int total_variables;
    char *ptr_variables[WEB_FIELDS_MAX];

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
                //This is to avoid crash in line
                w->url_search_path = NULL;
                if(w->mode != WEB_CLIENT_MODE_NORMAL) {
                    if(!url_decode_r(w->decoded_url, encoded_url, NETDATA_WEB_REQUEST_URL_SIZE + 1))
                        return HTTP_VALIDATION_MALFORMED_URL;
                } else {
                    web_client_split_path_query(w, encoded_url);

                    if (w->url_search_path && w->separator) {
                        *w->url_search_path = 0x00;
                    }

                    if(!url_decode_r(w->decoded_url, encoded_url, NETDATA_WEB_REQUEST_URL_SIZE + 1))
                        return HTTP_VALIDATION_MALFORMED_URL;

                    if (w->url_search_path && w->separator) {
                        *w->url_search_path = w->separator;

                        char *from = (encoded_url + w->url_path_length);
                        total_variables = url_map_query_string(ptr_variables, from);

                        if (url_parse_query_string(w->decoded_query_string, NETDATA_WEB_REQUEST_URL_SIZE + 1, ptr_variables, total_variables)) {
                            return HTTP_VALIDATION_MALFORMED_URL;
                        }
                    }
                }
                *ue = ' ';

                // copy the URL - we are going to overwrite parts of it
                // TODO -- ideally we we should avoid copying buffers around
                strncpyz(w->last_url, w->decoded_url, NETDATA_WEB_REQUEST_URL_SIZE);
#ifdef ENABLE_HTTPS
                if ( (!web_client_check_unix(w)) && (netdata_srv_ctx) ) {
                    if ((w->ssl.conn) && ((w->ssl.flags & NETDATA_SSL_NO_HANDSHAKE) && (web_client_is_using_ssl_force(w) || web_client_is_using_ssl_default(w)) && (w->mode != WEB_CLIENT_MODE_STREAM))  ) {
                        w->header_parse_tries = 0;
                        w->header_parse_last_size = 0;
                        web_client_disable_wait_receive(w);
                        return HTTP_VALIDATION_REDIRECT;
                    }
                }
#endif

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