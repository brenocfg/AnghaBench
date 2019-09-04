#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_3__ {scalar_t__ key; int /*<<< orphan*/ * lua_vm; } ;
typedef  TYPE_1__ ngx_http_lua_socket_pool_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  socket_pool_key ; 

__attribute__((used)) static void
ngx_http_lua_socket_free_pool(ngx_log_t *log, ngx_http_lua_socket_pool_t *spool)
{
    lua_State                           *L;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, log, 0,
                   "lua tcp socket keepalive: free connection pool for \"%s\"",
                   spool->key);

    L = spool->lua_vm;

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(socket_pool_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pushstring(L, (char *) spool->key);
    lua_pushnil(L);
    lua_rawset(L, -3);
    lua_pop(L, 1);
}