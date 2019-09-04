#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_17__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int /*<<< orphan*/  count; int /*<<< orphan*/  filter; TYPE_1__ method; } ;
typedef  TYPE_4__ ngx_rtmp_control_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_19__ {size_t content_length_n; int /*<<< orphan*/  status; } ;
struct TYPE_21__ {int /*<<< orphan*/  pool; TYPE_3__ headers_out; TYPE_2__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_22__ {TYPE_7__* buf; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_23__ {int temporary; int last_buf; int /*<<< orphan*/ * last; int /*<<< orphan*/ * end; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * start; } ;
typedef  TYPE_7__ ngx_buf_t ;
typedef  int /*<<< orphan*/  cl ;
struct TYPE_18__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 char const* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_OK ; 
 size_t NGX_INT_T_LEN ; 
 int /*<<< orphan*/  NGX_RTMP_CONTROL_FILTER_CLIENT ; 
 int /*<<< orphan*/  NGX_RTMP_CONTROL_FILTER_PUBLISHER ; 
 int /*<<< orphan*/  NGX_RTMP_CONTROL_FILTER_SUBSCRIBER ; 
 TYPE_7__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_output_filter (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_send_header (TYPE_5__*) ; 
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_rtmp_control_module ; 
 int /*<<< orphan*/  ngx_rtmp_control_redirect_handler ; 
 char* ngx_rtmp_control_walk (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_control_redirect(ngx_http_request_t *r, ngx_str_t *method)
{
    size_t                   len;
    u_char                  *p;
    ngx_buf_t               *b;
    ngx_chain_t              cl;
    const char              *msg;
    ngx_rtmp_control_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_rtmp_control_module);

    if (ctx->method.len == sizeof("publisher") - 1 &&
        ngx_memcmp(ctx->method.data, "publisher", ctx->method.len) == 0)
    {
        ctx->filter = NGX_RTMP_CONTROL_FILTER_PUBLISHER;

    } else if (ctx->method.len == sizeof("subscriber") - 1 &&
               ngx_memcmp(ctx->method.data, "subscriber", ctx->method.len)
               == 0)
    {
        ctx->filter = NGX_RTMP_CONTROL_FILTER_SUBSCRIBER;

    } else if (ctx->method.len == sizeof("client") - 1 &&
               ngx_memcmp(ctx->method.data, "client", ctx->method.len) == 0)
    {
        ctx->filter = NGX_RTMP_CONTROL_FILTER_CLIENT;

    } else {
        msg = "Undefined filter";
        goto error;
    }

    msg = ngx_rtmp_control_walk(r, ngx_rtmp_control_redirect_handler);
    if (msg != NGX_CONF_OK) {
        goto error;
    }

    /* output count */

    len = NGX_INT_T_LEN;

    p = ngx_palloc(r->connection->pool, len);
    if (p == NULL) {
        goto error;
    }

    len = (size_t) (ngx_snprintf(p, len, "%ui", ctx->count) - p);

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = len;

    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        goto error;
    }

    b->start = b->pos = p;
    b->end = b->last = p + len;
    b->temporary = 1;
    b->last_buf = 1;

    ngx_memzero(&cl, sizeof(cl));
    cl.buf = b;

    ngx_http_send_header(r);

    return ngx_http_output_filter(r, &cl);

error:
    return NGX_HTTP_INTERNAL_SERVER_ERROR;
}