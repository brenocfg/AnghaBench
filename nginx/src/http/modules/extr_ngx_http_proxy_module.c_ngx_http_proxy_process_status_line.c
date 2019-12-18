#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int connection_close; scalar_t__ status_n; TYPE_7__ status_line; } ;
struct TYPE_18__ {scalar_t__ (* process_header ) (TYPE_5__*) ;TYPE_3__ headers_in; TYPE_1__* state; scalar_t__ accel; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_19__ {TYPE_2__* connection; int /*<<< orphan*/  pool; void* http_version; scalar_t__ cache; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_14__ {scalar_t__ code; size_t end; size_t start; scalar_t__ http_version; } ;
struct TYPE_20__ {TYPE_11__ status; } ;
typedef  TYPE_6__ ngx_http_proxy_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_HTTP_UPSTREAM_INVALID_HEADER ; 
 scalar_t__ NGX_HTTP_VERSION_11 ; 
 void* NGX_HTTP_VERSION_9 ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_parse_status_line (TYPE_5__*,int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 
 scalar_t__ ngx_http_proxy_process_header (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_process_status_line(ngx_http_request_t *r)
{
    size_t                 len;
    ngx_int_t              rc;
    ngx_http_upstream_t   *u;
    ngx_http_proxy_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_module);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    u = r->upstream;

    rc = ngx_http_parse_status_line(r, &u->buffer, &ctx->status);

    if (rc == NGX_AGAIN) {
        return rc;
    }

    if (rc == NGX_ERROR) {

#if (NGX_HTTP_CACHE)

        if (r->cache) {
            r->http_version = NGX_HTTP_VERSION_9;
            return NGX_OK;
        }

#endif

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "upstream sent no valid HTTP/1.0 header");

#if 0
        if (u->accel) {
            return NGX_HTTP_UPSTREAM_INVALID_HEADER;
        }
#endif

        r->http_version = NGX_HTTP_VERSION_9;
        u->state->status = NGX_HTTP_OK;
        u->headers_in.connection_close = 1;

        return NGX_OK;
    }

    if (u->state && u->state->status == 0) {
        u->state->status = ctx->status.code;
    }

    u->headers_in.status_n = ctx->status.code;

    len = ctx->status.end - ctx->status.start;
    u->headers_in.status_line.len = len;

    u->headers_in.status_line.data = ngx_pnalloc(r->pool, len);
    if (u->headers_in.status_line.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(u->headers_in.status_line.data, ctx->status.start, len);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http proxy status %ui \"%V\"",
                   u->headers_in.status_n, &u->headers_in.status_line);

    if (ctx->status.http_version < NGX_HTTP_VERSION_11) {
        u->headers_in.connection_close = 1;
    }

    u->process_header = ngx_http_proxy_process_header;

    return ngx_http_proxy_process_header(r);
}