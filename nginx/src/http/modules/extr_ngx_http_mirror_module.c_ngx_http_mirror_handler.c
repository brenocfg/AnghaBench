#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/  pool; TYPE_1__* connection; struct TYPE_17__* main; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_18__ {scalar_t__ request_body; int /*<<< orphan*/ * mirror; } ;
typedef  TYPE_3__ ngx_http_mirror_loc_conf_t ;
struct TYPE_19__ {scalar_t__ status; } ;
typedef  TYPE_4__ ngx_http_mirror_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_2__*,scalar_t__) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_mirror_body_handler ; 
 scalar_t__ ngx_http_mirror_handler_internal (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_mirror_module ; 
 scalar_t__ ngx_http_read_client_request_body (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mirror_handler(ngx_http_request_t *r)
{
    ngx_int_t                    rc;
    ngx_http_mirror_ctx_t       *ctx;
    ngx_http_mirror_loc_conf_t  *mlcf;

    if (r != r->main) {
        return NGX_DECLINED;
    }

    mlcf = ngx_http_get_module_loc_conf(r, ngx_http_mirror_module);

    if (mlcf->mirror == NULL) {
        return NGX_DECLINED;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "mirror handler");

    if (mlcf->request_body) {
        ctx = ngx_http_get_module_ctx(r, ngx_http_mirror_module);

        if (ctx) {
            return ctx->status;
        }

        ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_mirror_ctx_t));
        if (ctx == NULL) {
            return NGX_ERROR;
        }

        ctx->status = NGX_DONE;

        ngx_http_set_ctx(r, ctx, ngx_http_mirror_module);

        rc = ngx_http_read_client_request_body(r, ngx_http_mirror_body_handler);
        if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
            return rc;
        }

        ngx_http_finalize_request(r, NGX_DONE);
        return NGX_DONE;
    }

    return ngx_http_mirror_handler_internal(r);
}