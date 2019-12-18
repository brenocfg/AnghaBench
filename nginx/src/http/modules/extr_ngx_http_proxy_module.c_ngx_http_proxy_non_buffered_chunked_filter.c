#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/  connection_close; } ;
struct TYPE_16__ {int /*<<< orphan*/  tag; } ;
struct TYPE_23__ {scalar_t__ pos; scalar_t__ last; int flush; int memory; int /*<<< orphan*/  tag; } ;
struct TYPE_19__ {int keepalive; scalar_t__ length; TYPE_2__ headers_in; TYPE_1__ output; int /*<<< orphan*/  free_bufs; TYPE_7__* out_bufs; TYPE_8__ buffer; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_20__ {TYPE_3__* connection; int /*<<< orphan*/  pool; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_21__ {TYPE_11__ chunked; } ;
typedef  TYPE_6__ ngx_http_proxy_ctx_t ;
struct TYPE_22__ {TYPE_8__* buf; struct TYPE_22__* next; } ;
typedef  TYPE_7__ ngx_chain_t ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_7__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_parse_chunked (TYPE_5__*,TYPE_8__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_module ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_non_buffered_chunked_filter(void *data, ssize_t bytes)
{
    ngx_http_request_t   *r = data;

    ngx_int_t              rc;
    ngx_buf_t             *b, *buf;
    ngx_chain_t           *cl, **ll;
    ngx_http_upstream_t   *u;
    ngx_http_proxy_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_module);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    u = r->upstream;
    buf = &u->buffer;

    buf->pos = buf->last;
    buf->last += bytes;

    for (cl = u->out_bufs, ll = &u->out_bufs; cl; cl = cl->next) {
        ll = &cl->next;
    }

    for ( ;; ) {

        rc = ngx_http_parse_chunked(r, buf, &ctx->chunked);

        if (rc == NGX_OK) {

            /* a chunk has been parsed successfully */

            cl = ngx_chain_get_free_buf(r->pool, &u->free_bufs);
            if (cl == NULL) {
                return NGX_ERROR;
            }

            *ll = cl;
            ll = &cl->next;

            b = cl->buf;

            b->flush = 1;
            b->memory = 1;

            b->pos = buf->pos;
            b->tag = u->output.tag;

            if (buf->last - buf->pos >= ctx->chunked.size) {
                buf->pos += (size_t) ctx->chunked.size;
                b->last = buf->pos;
                ctx->chunked.size = 0;

            } else {
                ctx->chunked.size -= buf->last - buf->pos;
                buf->pos = buf->last;
                b->last = buf->last;
            }

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http proxy out buf %p %z",
                           b->pos, b->last - b->pos);

            continue;
        }

        if (rc == NGX_DONE) {

            /* a whole response has been parsed successfully */

            u->keepalive = !u->headers_in.connection_close;
            u->length = 0;

            break;
        }

        if (rc == NGX_AGAIN) {
            break;
        }

        /* invalid response */

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "upstream sent invalid chunked response");

        return NGX_ERROR;
    }

    return NGX_OK;
}