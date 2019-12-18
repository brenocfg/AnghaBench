#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct web_client {int /*<<< orphan*/  server_host; void* auth_bearer_token; void* user_agent; int /*<<< orphan*/  origin; } ;

/* Variables and functions */
 size_t NETDATA_WEB_REQUEST_ORIGIN_HEADER_SIZE ; 
 scalar_t__ respect_web_browser_do_not_track_policy ; 
 scalar_t__ simple_uhash (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strcasestr (char*,char*) ; 
 void* strdupz (char*) ; 
 int /*<<< orphan*/  strncpyz (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  web_client_disable_donottrack (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_deflate (struct web_client*,int) ; 
 int /*<<< orphan*/  web_client_enable_donottrack (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_keepalive (struct web_client*) ; 
 scalar_t__ web_enable_gzip ; 

__attribute__((used)) static inline char *http_header_parse(struct web_client *w, char *s, int parse_useragent) {
    static uint32_t hash_origin = 0, hash_connection = 0, hash_donottrack = 0, hash_useragent = 0, hash_authorization = 0, hash_host = 0;
#ifdef NETDATA_WITH_ZLIB
    static uint32_t hash_accept_encoding = 0;
#endif

    if(unlikely(!hash_origin)) {
        hash_origin = simple_uhash("Origin");
        hash_connection = simple_uhash("Connection");
#ifdef NETDATA_WITH_ZLIB
        hash_accept_encoding = simple_uhash("Accept-Encoding");
#endif
        hash_donottrack = simple_uhash("DNT");
        hash_useragent = simple_uhash("User-Agent");
        hash_authorization = simple_uhash("X-Auth-Token");
        hash_host = simple_uhash("Host");
    }

    char *e = s;

    // find the :
    while(*e && *e != ':') e++;
    if(!*e) return e;

    // get the name
    *e = '\0';

    // find the value
    char *v = e + 1, *ve;

    // skip leading spaces from value
    while(*v == ' ') v++;
    ve = v;

    // find the \r
    while(*ve && *ve != '\r') ve++;
    if(!*ve || ve[1] != '\n') {
        *e = ':';
        return ve;
    }

    // terminate the value
    *ve = '\0';

    uint32_t hash = simple_uhash(s);

    if(hash == hash_origin && !strcasecmp(s, "Origin"))
        strncpyz(w->origin, v, NETDATA_WEB_REQUEST_ORIGIN_HEADER_SIZE);

    else if(hash == hash_connection && !strcasecmp(s, "Connection")) {
        if(strcasestr(v, "keep-alive"))
            web_client_enable_keepalive(w);
    }
    else if(respect_web_browser_do_not_track_policy && hash == hash_donottrack && !strcasecmp(s, "DNT")) {
        if(*v == '0') web_client_disable_donottrack(w);
        else if(*v == '1') web_client_enable_donottrack(w);
    }
    else if(parse_useragent && hash == hash_useragent && !strcasecmp(s, "User-Agent")) {
        w->user_agent = strdupz(v);
    } else if(hash == hash_authorization&& !strcasecmp(s, "X-Auth-Token")) {
        w->auth_bearer_token = strdupz(v);
    }
    else if(hash == hash_host && !strcasecmp(s, "Host")){
        strncpyz(w->server_host, v, ((size_t)(ve - v) < sizeof(w->server_host)-1 ? (size_t)(ve - v) : sizeof(w->server_host)-1));
    }
#ifdef NETDATA_WITH_ZLIB
    else if(hash == hash_accept_encoding && !strcasecmp(s, "Accept-Encoding")) {
        if(web_enable_gzip) {
            if(strcasestr(v, "gzip"))
                web_client_enable_deflate(w, 1);
            //
            // does not seem to work
            // else if(strcasestr(v, "deflate"))
            //  web_client_enable_deflate(w, 0);
        }
    }
#endif /* NETDATA_WITH_ZLIB */

    *e = ':';
    *ve = '\r';
    return ve;
}