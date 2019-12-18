#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_17__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {TYPE_2__ path; int /*<<< orphan*/  filter; } ;
typedef  TYPE_3__ ngx_rtmp_control_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {scalar_t__ content_length_n; int /*<<< orphan*/  status; } ;
struct TYPE_19__ {int /*<<< orphan*/  pool; TYPE_1__ headers_out; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_20__ {TYPE_6__* buf; } ;
typedef  TYPE_5__ ngx_chain_t ;
struct TYPE_21__ {int last_buf; int /*<<< orphan*/  pos; int /*<<< orphan*/  last; } ;
typedef  TYPE_6__ ngx_buf_t ;
typedef  int /*<<< orphan*/  cl ;

/* Variables and functions */
 char const* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_NO_CONTENT ; 
 int /*<<< orphan*/  NGX_HTTP_OK ; 
 int /*<<< orphan*/  NGX_RTMP_CONTROL_FILTER_PUBLISHER ; 
 int /*<<< orphan*/  ngx_cpymem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_6__* ngx_create_temp_buf (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_output_filter (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_send_header (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_control_module ; 
 int /*<<< orphan*/  ngx_rtmp_control_record_handler ; 
 char* ngx_rtmp_control_walk (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_control_record(ngx_http_request_t *r, ngx_str_t *method)
{
    ngx_buf_t               *b;
    const char              *msg;
    ngx_chain_t              cl;
    ngx_rtmp_control_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_rtmp_control_module);
    ctx->filter = NGX_RTMP_CONTROL_FILTER_PUBLISHER;

    msg = ngx_rtmp_control_walk(r, ngx_rtmp_control_record_handler);
    if (msg != NGX_CONF_OK) {
        goto error;
    }

    if (ctx->path.len == 0) {
        return NGX_HTTP_NO_CONTENT;
    }

    /* output record path */

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = ctx->path.len;

    b = ngx_create_temp_buf(r->pool, ctx->path.len);
    if (b == NULL) {
        goto error;
    }

    ngx_memzero(&cl, sizeof(cl));
    cl.buf = b;

    b->last = ngx_cpymem(b->pos, ctx->path.data, ctx->path.len);
    b->last_buf = 1;

    ngx_http_send_header(r);

    return ngx_http_output_filter(r, &cl);

error:
    return NGX_HTTP_INTERNAL_SERVER_ERROR;
}