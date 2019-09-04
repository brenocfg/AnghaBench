#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_21__ {int angle; scalar_t__ max_width; scalar_t__ max_height; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  force; } ;
typedef  TYPE_3__ ngx_http_image_filter_ctx_t ;
struct TYPE_22__ {scalar_t__ filter; int /*<<< orphan*/  height; int /*<<< orphan*/  hcv; int /*<<< orphan*/  width; int /*<<< orphan*/  wcv; int /*<<< orphan*/  angle; int /*<<< orphan*/  acv; } ;
typedef  TYPE_4__ ngx_http_image_filter_conf_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;
struct TYPE_19__ {int /*<<< orphan*/  buffered; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_IMAGE_BUFFERED ; 
 scalar_t__ NGX_HTTP_IMAGE_ROTATE ; 
 scalar_t__ NGX_HTTP_IMAGE_SIZE ; 
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_image_asis (TYPE_2__*,TYPE_3__*) ; 
 void* ngx_http_image_filter_get_value (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_image_filter_module ; 
 int /*<<< orphan*/ * ngx_http_image_json (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * ngx_http_image_resize (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ ngx_http_image_size (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static ngx_buf_t *
ngx_http_image_process(ngx_http_request_t *r)
{
    ngx_int_t                      rc;
    ngx_http_image_filter_ctx_t   *ctx;
    ngx_http_image_filter_conf_t  *conf;

    r->connection->buffered &= ~NGX_HTTP_IMAGE_BUFFERED;

    ctx = ngx_http_get_module_ctx(r, ngx_http_image_filter_module);

    rc = ngx_http_image_size(r, ctx);

    conf = ngx_http_get_module_loc_conf(r, ngx_http_image_filter_module);

    if (conf->filter == NGX_HTTP_IMAGE_SIZE) {
        return ngx_http_image_json(r, rc == NGX_OK ? ctx : NULL);
    }

    ctx->angle = ngx_http_image_filter_get_value(r, conf->acv, conf->angle);

    if (conf->filter == NGX_HTTP_IMAGE_ROTATE) {

        if (ctx->angle != 90 && ctx->angle != 180 && ctx->angle != 270) {
            return NULL;
        }

        return ngx_http_image_resize(r, ctx);
    }

    ctx->max_width = ngx_http_image_filter_get_value(r, conf->wcv, conf->width);
    if (ctx->max_width == 0) {
        return NULL;
    }

    ctx->max_height = ngx_http_image_filter_get_value(r, conf->hcv,
                                                      conf->height);
    if (ctx->max_height == 0) {
        return NULL;
    }

    if (rc == NGX_OK
        && ctx->width <= ctx->max_width
        && ctx->height <= ctx->max_height
        && ctx->angle == 0
        && !ctx->force)
    {
        return ngx_http_image_asis(r, ctx);
    }

    return ngx_http_image_resize(r, ctx);
}