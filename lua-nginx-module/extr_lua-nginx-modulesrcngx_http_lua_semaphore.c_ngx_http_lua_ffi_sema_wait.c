#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_18__ {scalar_t__ prev; } ;
struct TYPE_21__ {scalar_t__ resource_count; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  wait_count; TYPE_1__ sem_event; } ;
typedef  TYPE_4__ ngx_http_lua_sema_t ;
struct TYPE_22__ {TYPE_6__* cur_co_ctx; } ;
typedef  TYPE_5__ ngx_http_lua_ctx_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; TYPE_6__* data; int /*<<< orphan*/  handler; } ;
struct TYPE_23__ {int /*<<< orphan*/  cleanup; TYPE_4__* data; int /*<<< orphan*/  sem_wait_queue; TYPE_14__ sleep; } ;
typedef  TYPE_6__ ngx_http_lua_co_ctx_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; } ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
 int NGX_DECLINED ; 
 int NGX_ERROR ; 
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_14__*,int /*<<< orphan*/ ) ; 
 TYPE_13__* ngx_cycle ; 
 TYPE_5__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_ffi_check_context (TYPE_5__*,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_sema_cleanup ; 
 int /*<<< orphan*/  ngx_http_lua_sema_timeout_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*,int,scalar_t__,int) ; 
 scalar_t__ ngx_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,size_t,char*) ; 

int
ngx_http_lua_ffi_sema_wait(ngx_http_request_t *r,
    ngx_http_lua_sema_t *sem, int wait_ms, u_char *err, size_t *errlen)
{
    ngx_http_lua_ctx_t           *ctx;
    ngx_http_lua_co_ctx_t        *wait_co_ctx;
    ngx_int_t                     rc;

    ngx_log_debug4(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "http lua semaphore wait: %p, timeout: %d, "
                   "resources: %d, event posted: %d",
                   sem, wait_ms, sem->resource_count,
#if (nginx_version >= 1007005)
                   (int) sem->sem_event.posted
#else
                   sem->sem_event.prev ? 1 : 0
#endif
                   );

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        *errlen = ngx_snprintf(err, *errlen, "no request ctx found") - err;
        return NGX_ERROR;
    }

    rc = ngx_http_lua_ffi_check_context(ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                                        | NGX_HTTP_LUA_CONTEXT_ACCESS
                                        | NGX_HTTP_LUA_CONTEXT_CONTENT
                                        | NGX_HTTP_LUA_CONTEXT_TIMER
                                        | NGX_HTTP_LUA_CONTEXT_SSL_CERT,
                                        err, errlen);

    if (rc != NGX_OK) {
        return NGX_ERROR;
    }

    /* we keep the order, will first resume the thread waiting for the
     * longest time in ngx_http_lua_sema_handler
     */

    if (ngx_queue_empty(&sem->wait_queue) && sem->resource_count > 0) {
        sem->resource_count--;
        return NGX_OK;
    }

    if (wait_ms == 0) {
        return NGX_DECLINED;
    }

    sem->wait_count++;
    wait_co_ctx = ctx->cur_co_ctx;

    wait_co_ctx->sleep.handler = ngx_http_lua_sema_timeout_handler;
    wait_co_ctx->sleep.data = ctx->cur_co_ctx;
    wait_co_ctx->sleep.log = r->connection->log;

    ngx_add_timer(&wait_co_ctx->sleep, (ngx_msec_t) wait_ms);

    dd("ngx_http_lua_ffi_sema_wait add timer coctx:%p wait: %d(ms)",
       wait_co_ctx, wait_ms);

    ngx_queue_insert_tail(&sem->wait_queue, &wait_co_ctx->sem_wait_queue);

    wait_co_ctx->data = sem;
    wait_co_ctx->cleanup = ngx_http_lua_sema_cleanup;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "http lua semaphore wait yielding");

    return NGX_AGAIN;
}