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
struct TYPE_2__ {scalar_t__ flags; } ;
struct web_client {int /*<<< orphan*/  mode; scalar_t__ header_parse_last_size; scalar_t__ header_parse_tries; TYPE_1__ ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  WEB_CLIENT_MODE_NORMAL ; 
 int /*<<< orphan*/  WEB_CLIENT_MODE_OPTIONS ; 
 int /*<<< orphan*/  WEB_CLIENT_MODE_STREAM ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  web_client_disable_wait_receive (struct web_client*) ; 
 scalar_t__ web_client_is_using_ssl_force (struct web_client*) ; 

__attribute__((used)) static inline char *web_client_valid_method(struct web_client *w, char *s) {
    // is is a valid request?
    if(!strncmp(s, "GET ", 4)) {
        s = &s[4];
        w->mode = WEB_CLIENT_MODE_NORMAL;
    }
    else if(!strncmp(s, "OPTIONS ", 8)) {
        s = &s[8];
        w->mode = WEB_CLIENT_MODE_OPTIONS;
    }
    else if(!strncmp(s, "STREAM ", 7)) {
        s = &s[7];

#ifdef ENABLE_HTTPS
        if (w->ssl.flags && web_client_is_using_ssl_force(w)){
            w->header_parse_tries = 0;
            w->header_parse_last_size = 0;
            web_client_disable_wait_receive(w);

            char hostname[256];
            char *copyme = strstr(s,"hostname=");
            if ( copyme ){
                copyme += 9;
                char *end = strchr(copyme,'&');
                if(end){
                    size_t length = end - copyme;
                    memcpy(hostname,copyme,length);
                    hostname[length] = 0X00;
                }
                else{
                    memcpy(hostname,"not available",13);
                    hostname[13] = 0x00;
                }
            }
            else{
                memcpy(hostname,"not available",13);
                hostname[13] = 0x00;
            }
            error("The server is configured to always use encrypt connection, please enable the SSL on slave with hostname '%s'.",hostname);
            s = NULL;
        }
#endif

        w->mode = WEB_CLIENT_MODE_STREAM;
    }
    else {
        s = NULL;
    }

    return s;
}