#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ref; int /*<<< orphan*/ * vm; } ;
typedef  TYPE_1__ ngx_http_lua_ngx_ctx_cleanup_data_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_lua_ctx_tables_key ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_lua_ngx_ctx_cleanup(void *data)
{
    lua_State       *L;

    ngx_http_lua_ngx_ctx_cleanup_data_t    *clndata = data;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "lua release ngx.ctx at ref %d", clndata->ref);

    L = clndata->vm;

    lua_pushliteral(L, ngx_http_lua_ctx_tables_key);
    lua_rawget(L, LUA_REGISTRYINDEX);
    luaL_unref(L, -1, clndata->ref);
    lua_pop(L, 1);
}