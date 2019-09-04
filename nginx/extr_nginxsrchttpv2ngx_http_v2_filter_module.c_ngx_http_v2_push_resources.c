#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_19__ {char* data; int len; } ;
struct TYPE_24__ {TYPE_10__ value; } ;
typedef  TYPE_5__ ngx_table_elt_t ;
struct TYPE_25__ {int len; char* data; } ;
typedef  TYPE_6__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {int /*<<< orphan*/  push_preload; TYPE_1__* pushes; } ;
typedef  TYPE_7__ ngx_http_v2_loc_conf_t ;
struct TYPE_21__ {size_t nelts; TYPE_5__** elts; } ;
struct TYPE_22__ {TYPE_2__ link; } ;
struct TYPE_27__ {TYPE_4__* connection; TYPE_3__ headers_out; } ;
typedef  TYPE_8__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_complex_value_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;
struct TYPE_20__ {size_t nelts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_V2_PUSH_HEADERS ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_complex_value (TYPE_8__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 scalar_t__ ngx_http_v2_push_resource (TYPE_8__*,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 char* ngx_strlchr (char*,char*,char) ; 
 scalar_t__ ngx_strncasecmp (char*,char*,int) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_push_resources(ngx_http_request_t *r)
{
    u_char                     *start, *end, *last;
    ngx_int_t                   rc;
    ngx_str_t                   path;
    ngx_uint_t                  i, push;
    ngx_table_elt_t           **h;
    ngx_http_v2_loc_conf_t     *h2lcf;
    ngx_http_complex_value_t   *pushes;
    ngx_str_t                   binary[NGX_HTTP_V2_PUSH_HEADERS];

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http2 push resources");

    ngx_memzero(binary, NGX_HTTP_V2_PUSH_HEADERS * sizeof(ngx_str_t));

    h2lcf = ngx_http_get_module_loc_conf(r, ngx_http_v2_module);

    if (h2lcf->pushes) {
        pushes = h2lcf->pushes->elts;

        for (i = 0; i < h2lcf->pushes->nelts; i++) {

            if (ngx_http_complex_value(r, &pushes[i], &path) != NGX_OK) {
                return NGX_ERROR;
            }

            if (path.len == 0) {
                continue;
            }

            if (path.len == 3 && ngx_strncmp(path.data, "off", 3) == 0) {
                continue;
            }

            rc = ngx_http_v2_push_resource(r, &path, binary);

            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }

            if (rc == NGX_ABORT) {
                return NGX_OK;
            }

            /* NGX_OK, NGX_DECLINED */
        }
    }

    if (!h2lcf->push_preload) {
        return NGX_OK;
    }

    h = r->headers_out.link.elts;

    for (i = 0; i < r->headers_out.link.nelts; i++) {

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http2 parse link: \"%V\"", &h[i]->value);

        start = h[i]->value.data;
        end = h[i]->value.data + h[i]->value.len;

    next_link:

        while (start < end && *start == ' ') { start++; }

        if (start == end || *start++ != '<') {
            continue;
        }

        while (start < end && *start == ' ') { start++; }

        for (last = start; last < end && *last != '>'; last++) {
            /* void */
        }

        if (last == start || last == end) {
            continue;
        }

        path.len = last - start;
        path.data = start;

        start = last + 1;

        while (start < end && *start == ' ') { start++; }

        if (start == end) {
            continue;
        }

        if (*start == ',') {
            start++;
            goto next_link;
        }

        if (*start++ != ';') {
            continue;
        }

        last = ngx_strlchr(start, end, ',');

        if (last == NULL) {
            last = end;
        }

        push = 0;

        for ( ;; ) {

            while (start < last && *start == ' ') { start++; }

            if (last - start >= 6
                && ngx_strncasecmp(start, (u_char *) "nopush", 6) == 0)
            {
                start += 6;

                if (start == last || *start == ' ' || *start == ';') {
                    push = 0;
                    break;
                }

                goto next_param;
            }

            if (last - start >= 11
                && ngx_strncasecmp(start, (u_char *) "rel=preload", 11) == 0)
            {
                start += 11;

                if (start == last || *start == ' ' || *start == ';') {
                    push = 1;
                }

                goto next_param;
            }

            if (last - start >= 4
                && ngx_strncasecmp(start, (u_char *) "rel=", 4) == 0)
            {
                start += 4;

                while (start < last && *start == ' ') { start++; }

                if (start == last || *start++ != '"') {
                    goto next_param;
                }

                for ( ;; ) {

                    while (start < last && *start == ' ') { start++; }

                    if (last - start >= 7
                        && ngx_strncasecmp(start, (u_char *) "preload", 7) == 0)
                    {
                        start += 7;

                        if (start < last && (*start == ' ' || *start == '"')) {
                            push = 1;
                            break;
                        }
                    }

                    while (start < last && *start != ' ' && *start != '"') {
                        start++;
                    }

                    if (start == last) {
                        break;
                    }

                    if (*start == '"') {
                        break;
                    }

                    start++;
                }
            }

        next_param:

            start = ngx_strlchr(start, last, ';');

            if (start == NULL) {
                break;
            }

            start++;
        }

        if (push) {
            while (path.len && path.data[path.len - 1] == ' ') {
                path.len--;
            }
        }

        if (push && path.len
            && !(path.len > 1 && path.data[0] == '/' && path.data[1] == '/'))
        {
            rc = ngx_http_v2_push_resource(r, &path, binary);

            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }

            if (rc == NGX_ABORT) {
                return NGX_OK;
            }

            /* NGX_OK, NGX_DECLINED */
        }

        if (last < end) {
            start = last + 1;
            goto next_link;
        }
    }

    return NGX_OK;
}