#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_18__ {TYPE_4__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_19__ {scalar_t__ entered_content_phase; TYPE_3__* cur_co_ctx; int /*<<< orphan*/  resume_handler; } ;
typedef  TYPE_2__ ngx_http_lua_ctx_t ;
struct TYPE_20__ {scalar_t__ nsubreqs; int /*<<< orphan*/ * sr_flags; int /*<<< orphan*/ * sr_bodies; int /*<<< orphan*/ * sr_headers; int /*<<< orphan*/ * sr_statuses; } ;
typedef  TYPE_3__ ngx_http_lua_co_ctx_t ;
struct TYPE_21__ {int /*<<< orphan*/  log; int /*<<< orphan*/  requests; } ;
typedef  TYPE_4__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 TYPE_2__* ngx_http_get_module_ctx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_finalize_request (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_lua_vm (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_lua_handle_subreq_responses (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_run_posted_threads (TYPE_4__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_run_thread (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_lua_wev_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_subrequest_resume(ngx_http_request_t *r)
{
    lua_State                   *vm;
    ngx_int_t                    rc;
    ngx_uint_t                   nreqs;
    ngx_connection_t            *c;
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_lua_co_ctx_t       *coctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ctx->resume_handler = ngx_http_lua_wev_handler;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua run subrequests done, resuming lua thread");

    coctx = ctx->cur_co_ctx;

    dd("nsubreqs: %d", (int) coctx->nsubreqs);

    ngx_http_lua_handle_subreq_responses(r, ctx);

    dd("free sr_statues/headers/bodies memory ASAP");

#if 1
    ngx_pfree(r->pool, coctx->sr_statuses);

    coctx->sr_statuses = NULL;
    coctx->sr_headers = NULL;
    coctx->sr_bodies = NULL;
    coctx->sr_flags = NULL;
#endif

    c = r->connection;
    vm = ngx_http_lua_get_lua_vm(r, ctx);
    nreqs = c->requests;

    rc = ngx_http_lua_run_thread(vm, r, ctx, coctx->nsubreqs);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua run thread returned %d", rc);

    if (rc == NGX_AGAIN) {
        return ngx_http_lua_run_posted_threads(c, vm, r, ctx, nreqs);
    }

    if (rc == NGX_DONE) {
        ngx_http_lua_finalize_request(r, NGX_DONE);
        return ngx_http_lua_run_posted_threads(c, vm, r, ctx, nreqs);
    }

    /* rc == NGX_ERROR || rc >= NGX_OK */

    if (ctx->entered_content_phase) {
        ngx_http_lua_finalize_request(r, rc);
        return NGX_DONE;
    }

    return rc;
}