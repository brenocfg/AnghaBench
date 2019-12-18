#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {scalar_t__ status_n; int content_length_n; int /*<<< orphan*/  connection_close; scalar_t__ chunked; } ;
struct TYPE_12__ {int length; int keepalive; TYPE_3__ headers_in; TYPE_2__* pipe; int /*<<< orphan*/  input_filter; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_13__ {TYPE_1__* connection; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_14__ {scalar_t__ head; } ;
typedef  TYPE_6__ ngx_http_proxy_ctx_t ;
struct TYPE_10__ {int length; int /*<<< orphan*/  input_filter; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_NOT_MODIFIED ; 
 scalar_t__ NGX_HTTP_NO_CONTENT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_chunked_filter ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 
 int /*<<< orphan*/  ngx_http_proxy_non_buffered_chunked_filter ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_input_filter_init(void *data)
{
    ngx_http_request_t    *r = data;
    ngx_http_upstream_t   *u;
    ngx_http_proxy_ctx_t  *ctx;

    u = r->upstream;
    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_module);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http proxy filter init s:%ui h:%d c:%d l:%O",
                   u->headers_in.status_n, ctx->head, u->headers_in.chunked,
                   u->headers_in.content_length_n);

    /* as per RFC2616, 4.4 Message Length */

    if (u->headers_in.status_n == NGX_HTTP_NO_CONTENT
        || u->headers_in.status_n == NGX_HTTP_NOT_MODIFIED
        || ctx->head)
    {
        /* 1xx, 204, and 304 and replies to HEAD requests */
        /* no 1xx since we don't send Expect and Upgrade */

        u->pipe->length = 0;
        u->length = 0;
        u->keepalive = !u->headers_in.connection_close;

    } else if (u->headers_in.chunked) {
        /* chunked */

        u->pipe->input_filter = ngx_http_proxy_chunked_filter;
        u->pipe->length = 3; /* "0" LF LF */

        u->input_filter = ngx_http_proxy_non_buffered_chunked_filter;
        u->length = 1;

    } else if (u->headers_in.content_length_n == 0) {
        /* empty body: special case as filter won't be called */

        u->pipe->length = 0;
        u->length = 0;
        u->keepalive = !u->headers_in.connection_close;

    } else {
        /* content length or connection close */

        u->pipe->length = u->headers_in.content_length_n;
        u->length = u->headers_in.content_length_n;
    }

    return NGX_OK;
}