#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {scalar_t__ header_only; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_21__ {int before_body_sent; } ;
typedef  TYPE_3__ ngx_http_addition_ctx_t ;
struct TYPE_24__ {scalar_t__ len; } ;
struct TYPE_22__ {TYPE_7__ after_body; TYPE_7__ before_body; } ;
typedef  TYPE_4__ ngx_http_addition_conf_t ;
struct TYPE_23__ {TYPE_1__* buf; struct TYPE_23__* next; } ;
typedef  TYPE_5__ ngx_chain_t ;
struct TYPE_19__ {int last_in_chain; int sync; scalar_t__ last_buf; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LAST ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_addition_filter_module ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_next_body_filter (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ ngx_http_send_special (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_subrequest (TYPE_2__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_addition_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    ngx_int_t                  rc;
    ngx_uint_t                 last;
    ngx_chain_t               *cl;
    ngx_http_request_t        *sr;
    ngx_http_addition_ctx_t   *ctx;
    ngx_http_addition_conf_t  *conf;

    if (in == NULL || r->header_only) {
        return ngx_http_next_body_filter(r, in);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_addition_filter_module);

    if (ctx == NULL) {
        return ngx_http_next_body_filter(r, in);
    }

    conf = ngx_http_get_module_loc_conf(r, ngx_http_addition_filter_module);

    if (!ctx->before_body_sent) {
        ctx->before_body_sent = 1;

        if (conf->before_body.len) {
            if (ngx_http_subrequest(r, &conf->before_body, NULL, &sr, NULL, 0)
                != NGX_OK)
            {
                return NGX_ERROR;
            }
        }
    }

    if (conf->after_body.len == 0) {
        ngx_http_set_ctx(r, NULL, ngx_http_addition_filter_module);
        return ngx_http_next_body_filter(r, in);
    }

    last = 0;

    for (cl = in; cl; cl = cl->next) {
        if (cl->buf->last_buf) {
            cl->buf->last_buf = 0;
            cl->buf->last_in_chain = 1;
            cl->buf->sync = 1;
            last = 1;
        }
    }

    rc = ngx_http_next_body_filter(r, in);

    if (rc == NGX_ERROR || !last || conf->after_body.len == 0) {
        return rc;
    }

    if (ngx_http_subrequest(r, &conf->after_body, NULL, &sr, NULL, 0)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    ngx_http_set_ctx(r, NULL, ngx_http_addition_filter_module);

    return ngx_http_send_special(r, NGX_HTTP_LAST);
}