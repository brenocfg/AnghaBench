#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_14__ {int /*<<< orphan*/  avail_out; int /*<<< orphan*/  next_out; } ;
struct TYPE_17__ {scalar_t__ bufs; int nomem; TYPE_2__ zstream; TYPE_11__* out_buf; TYPE_1__* free; } ;
typedef  TYPE_5__ ngx_http_gunzip_ctx_t ;
struct TYPE_15__ {scalar_t__ num; int /*<<< orphan*/  size; } ;
struct TYPE_18__ {TYPE_3__ bufs; } ;
typedef  TYPE_6__ ngx_http_gunzip_conf_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_13__ {struct TYPE_13__* next; TYPE_11__* buf; } ;
struct TYPE_12__ {int recycled; int /*<<< orphan*/  pos; scalar_t__ tag; scalar_t__ flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_11__* ngx_create_temp_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_gunzip_filter_module ; 

__attribute__((used)) static ngx_int_t
ngx_http_gunzip_filter_get_buf(ngx_http_request_t *r,
    ngx_http_gunzip_ctx_t *ctx)
{
    ngx_http_gunzip_conf_t  *conf;

    if (ctx->zstream.avail_out) {
        return NGX_OK;
    }

    conf = ngx_http_get_module_loc_conf(r, ngx_http_gunzip_filter_module);

    if (ctx->free) {
        ctx->out_buf = ctx->free->buf;
        ctx->free = ctx->free->next;

        ctx->out_buf->flush = 0;

    } else if (ctx->bufs < conf->bufs.num) {

        ctx->out_buf = ngx_create_temp_buf(r->pool, conf->bufs.size);
        if (ctx->out_buf == NULL) {
            return NGX_ERROR;
        }

        ctx->out_buf->tag = (ngx_buf_tag_t) &ngx_http_gunzip_filter_module;
        ctx->out_buf->recycled = 1;
        ctx->bufs++;

    } else {
        ctx->nomem = 1;
        return NGX_DECLINED;
    }

    ctx->zstream.next_out = ctx->out_buf->pos;
    ctx->zstream.avail_out = conf->bufs.size;

    return NGX_OK;
}