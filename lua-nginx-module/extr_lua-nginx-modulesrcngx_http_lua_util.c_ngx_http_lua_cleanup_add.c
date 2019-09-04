#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* cleanup; TYPE_1__* connection; struct TYPE_14__* main; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_15__ {TYPE_4__* free_cleanup; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
struct TYPE_16__ {struct TYPE_16__* next; int /*<<< orphan*/ * handler; } ;
typedef  TYPE_4__ ngx_http_cleanup_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,TYPE_4__*) ; 
 TYPE_4__* ngx_http_cleanup_add (TYPE_2__*,size_t) ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 

ngx_http_cleanup_t *
ngx_http_lua_cleanup_add(ngx_http_request_t *r, size_t size)
{
    ngx_http_cleanup_t  *cln;
    ngx_http_lua_ctx_t  *ctx;

    if (size == 0) {
        ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

        r = r->main;

        if (ctx != NULL && ctx->free_cleanup) {
            cln = ctx->free_cleanup;
            ctx->free_cleanup = cln->next;

            dd("reuse cleanup: %p", cln);

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "lua http cleanup reuse: %p", cln);

            cln->handler = NULL;
            cln->next = r->cleanup;

            r->cleanup = cln;

            return cln;
        }
    }

    return ngx_http_cleanup_add(r, size);
}