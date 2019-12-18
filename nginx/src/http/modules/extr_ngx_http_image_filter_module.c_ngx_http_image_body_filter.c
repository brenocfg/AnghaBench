#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_28__ {int /*<<< orphan*/ * content_type_lowcase; TYPE_3__ content_type; int /*<<< orphan*/  content_type_len; } ;
struct TYPE_30__ {TYPE_2__ headers_out; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_31__ {int phase; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ ngx_http_image_filter_ctx_t ;
struct TYPE_32__ {int /*<<< orphan*/  filter; } ;
typedef  TYPE_6__ ngx_http_image_filter_conf_t ;
struct TYPE_33__ {int /*<<< orphan*/ * next; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
struct TYPE_27__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_IMAGE_DONE ; 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_NONE ; 
#define  NGX_HTTP_IMAGE_PASS 131 
#define  NGX_HTTP_IMAGE_PROCESS 130 
#define  NGX_HTTP_IMAGE_READ 129 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_SIZE ; 
#define  NGX_HTTP_IMAGE_START 128 
 int /*<<< orphan*/  NGX_HTTP_IMAGE_TEST ; 
 int /*<<< orphan*/  NGX_HTTP_UNSUPPORTED_MEDIA_TYPE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_filter_finalize_request (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_image_filter_module ; 
 int /*<<< orphan*/ * ngx_http_image_json (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_image_process (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_image_read (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_image_send (TYPE_4__*,TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_image_test (TYPE_4__*,TYPE_7__*) ; 
 TYPE_3__* ngx_http_image_types ; 
 int /*<<< orphan*/  ngx_http_next_body_filter (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_image_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_int_t                      rc;
    ngx_str_t                     *ct;
    ngx_chain_t                    out;
    ngx_http_image_filter_ctx_t   *ctx;
    ngx_http_image_filter_conf_t  *conf;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "image filter");

    if (in == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_image_filter_module);

    if (ctx == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    switch (ctx->phase) {

    case NGX_HTTP_IMAGE_START:

        ctx->type = ngx_http_image_test(r, in);

        conf = ngx_http_get_module_loc_conf(r, ngx_http_image_filter_module);

        if (ctx->type == NGX_HTTP_IMAGE_NONE) {

            if (conf->filter == NGX_HTTP_IMAGE_SIZE) {
                out.buf = ngx_http_image_json(r, NULL);

                if (out.buf) {
                    out.next = NULL;
                    ctx->phase = NGX_HTTP_IMAGE_DONE;

                    return ngx_http_image_send(r, ctx, &out);
                }
            }

            return ngx_http_filter_finalize_request(r,
                                              &ngx_http_image_filter_module,
                                              NGX_HTTP_UNSUPPORTED_MEDIA_TYPE);
        }

        /* override content type */

        ct = &ngx_http_image_types[ctx->type - 1];
        r->headers_out.content_type_len = ct->len;
        r->headers_out.content_type = *ct;
        r->headers_out.content_type_lowcase = NULL;

        if (conf->filter == NGX_HTTP_IMAGE_TEST) {
            ctx->phase = NGX_HTTP_IMAGE_PASS;

            return ngx_http_image_send(r, ctx, in);
        }

        ctx->phase = NGX_HTTP_IMAGE_READ;

        /* fall through */

    case NGX_HTTP_IMAGE_READ:

        rc = ngx_http_image_read(r, in);

        if (rc == NGX_AGAIN) {
            return NGX_OK;
        }

        if (rc == NGX_ERROR) {
            return ngx_http_filter_finalize_request(r,
                                              &ngx_http_image_filter_module,
                                              NGX_HTTP_UNSUPPORTED_MEDIA_TYPE);
        }

        /* fall through */

    case NGX_HTTP_IMAGE_PROCESS:

        out.buf = ngx_http_image_process(r);

        if (out.buf == NULL) {
            return ngx_http_filter_finalize_request(r,
                                              &ngx_http_image_filter_module,
                                              NGX_HTTP_UNSUPPORTED_MEDIA_TYPE);
        }

        out.next = NULL;
        ctx->phase = NGX_HTTP_IMAGE_PASS;

        return ngx_http_image_send(r, ctx, &out);

    case NGX_HTTP_IMAGE_PASS:

        return ngx_http_next_body_filter(r, in);

    default: /* NGX_HTTP_IMAGE_DONE */

        rc = ngx_http_next_body_filter(r, NULL);

        /* NGX_ERROR resets any pending data */
        return (rc == NGX_OK) ? NGX_ERROR : rc;
    }
}