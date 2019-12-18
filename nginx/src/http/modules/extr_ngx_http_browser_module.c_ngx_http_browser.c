#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_20__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ ngx_str_t ;
struct TYPE_16__ {TYPE_2__* user_agent; } ;
struct TYPE_21__ {TYPE_5__* connection; TYPE_3__ headers_in; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_22__ {int skip; size_t version; int /*<<< orphan*/  add; int /*<<< orphan*/  name; } ;
typedef  TYPE_9__ ngx_http_modern_browser_t ;
struct TYPE_13__ {scalar_t__ modern_unlisted_browsers; TYPE_6__* ancient_browsers; scalar_t__ netscape4; TYPE_4__* modern_browsers; } ;
typedef  TYPE_10__ ngx_http_browser_conf_t ;
struct TYPE_19__ {size_t nelts; TYPE_7__* elts; } ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;
struct TYPE_17__ {size_t nelts; TYPE_9__* elts; } ;
struct TYPE_14__ {char* data; size_t len; } ;
struct TYPE_15__ {TYPE_1__ value; } ;

/* Variables and functions */
 size_t NGX_HTTP_ANCIENT_BROWSER ; 
 size_t NGX_HTTP_MODERN_BROWSER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * ngx_strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_uint_t
ngx_http_browser(ngx_http_request_t *r, ngx_http_browser_conf_t *cf)
{
    size_t                      len;
    u_char                     *name, *ua, *last, c;
    ngx_str_t                  *ancient;
    ngx_uint_t                  i, version, ver, scale;
    ngx_http_modern_browser_t  *modern;

    if (r->headers_in.user_agent == NULL) {
        if (cf->modern_unlisted_browsers) {
            return NGX_HTTP_MODERN_BROWSER;
        }

        return NGX_HTTP_ANCIENT_BROWSER;
    }

    ua = r->headers_in.user_agent->value.data;
    len = r->headers_in.user_agent->value.len;
    last = ua + len;

    if (cf->modern_browsers) {
        modern = cf->modern_browsers->elts;

        for (i = 0; i < cf->modern_browsers->nelts; i++) {
            name = ua + modern[i].skip;

            if (name >= last) {
                continue;
            }

            name = (u_char *) ngx_strstr(name, modern[i].name);

            if (name == NULL) {
                continue;
            }

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "browser: \"%s\"", name);

            name += modern[i].add;

            if (name >= last) {
                continue;
            }

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "version: \"%ui\" \"%s\"", modern[i].version, name);

            version = 0;
            ver = 0;
            scale = 1000000;

            while (name < last) {

                c = *name++;

                if (c >= '0' && c <= '9') {
                    ver = ver * 10 + (c - '0');
                    continue;
                }

                if (c == '.') {
                    version += ver * scale;

                    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                                   "version: \"%ui\" \"%ui\"",
                                   modern[i].version, version);

                    if (version > modern[i].version) {
                        return NGX_HTTP_MODERN_BROWSER;
                    }

                    ver = 0;
                    scale /= 100;
                    continue;
                }

                break;
            }

            version += ver * scale;

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "version: \"%ui\" \"%ui\"",
                           modern[i].version, version);

            if (version >= modern[i].version) {
                return NGX_HTTP_MODERN_BROWSER;
            }

            return NGX_HTTP_ANCIENT_BROWSER;
        }

        if (!cf->modern_unlisted_browsers) {
            return NGX_HTTP_ANCIENT_BROWSER;
        }
    }

    if (cf->netscape4) {
        if (len > sizeof("Mozilla/4.72 ") - 1
            && ngx_strncmp(ua, "Mozilla/", sizeof("Mozilla/") - 1) == 0
            && ua[8] > '0' && ua[8] < '5')
        {
            return NGX_HTTP_ANCIENT_BROWSER;
        }
    }

    if (cf->ancient_browsers) {
        ancient = cf->ancient_browsers->elts;

        for (i = 0; i < cf->ancient_browsers->nelts; i++) {
            if (len >= ancient[i].len
                && ngx_strstr(ua, ancient[i].data) != NULL)
            {
                return NGX_HTTP_ANCIENT_BROWSER;
            }
        }
    }

    if (cf->modern_unlisted_browsers) {
        return NGX_HTTP_MODERN_BROWSER;
    }

    return NGX_HTTP_ANCIENT_BROWSER;
}