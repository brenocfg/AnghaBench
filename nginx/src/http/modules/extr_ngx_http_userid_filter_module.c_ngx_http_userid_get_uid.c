#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_24__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ ngx_table_elt_t ;
struct TYPE_25__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  size_t ngx_int_t ;
struct TYPE_26__ {int /*<<< orphan*/ * uid_got; TYPE_4__ cookie; } ;
typedef  TYPE_5__ ngx_http_userid_ctx_t ;
struct TYPE_27__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ ngx_http_userid_conf_t ;
struct TYPE_21__ {TYPE_3__** elts; } ;
struct TYPE_22__ {TYPE_15__ cookies; } ;
struct TYPE_28__ {TYPE_2__* connection; TYPE_1__ headers_in; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 size_t NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ ngx_decode_base64 (TYPE_4__*,TYPE_4__*) ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_7__*,int /*<<< orphan*/ ) ; 
 size_t ngx_http_parse_multi_header_lines (TYPE_15__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_userid_filter_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_http_userid_ctx_t *
ngx_http_userid_get_uid(ngx_http_request_t *r, ngx_http_userid_conf_t *conf)
{
    ngx_int_t                n;
    ngx_str_t                src, dst;
    ngx_table_elt_t        **cookies;
    ngx_http_userid_ctx_t   *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_userid_filter_module);

    if (ctx) {
        return ctx;
    }

    if (ctx == NULL) {
        ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_userid_ctx_t));
        if (ctx == NULL) {
            return NULL;
        }

        ngx_http_set_ctx(r, ctx, ngx_http_userid_filter_module);
    }

    n = ngx_http_parse_multi_header_lines(&r->headers_in.cookies, &conf->name,
                                          &ctx->cookie);
    if (n == NGX_DECLINED) {
        return ctx;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "uid cookie: \"%V\"", &ctx->cookie);

    if (ctx->cookie.len < 22) {
        cookies = r->headers_in.cookies.elts;
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "client sent too short userid cookie \"%V\"",
                      &cookies[n]->value);
        return ctx;
    }

    src = ctx->cookie;

    /*
     * we have to limit the encoded string to 22 characters because
     *  1) cookie may be marked by "userid_mark",
     *  2) and there are already the millions cookies with a garbage
     *     instead of the correct base64 trail "=="
     */

    src.len = 22;

    dst.data = (u_char *) ctx->uid_got;

    if (ngx_decode_base64(&dst, &src) == NGX_ERROR) {
        cookies = r->headers_in.cookies.elts;
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "client sent invalid userid cookie \"%V\"",
                      &cookies[n]->value);
        return ctx;
    }

    ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "uid: %08XD%08XD%08XD%08XD",
                   ctx->uid_got[0], ctx->uid_got[1],
                   ctx->uid_got[2], ctx->uid_got[3]);

    return ctx;
}