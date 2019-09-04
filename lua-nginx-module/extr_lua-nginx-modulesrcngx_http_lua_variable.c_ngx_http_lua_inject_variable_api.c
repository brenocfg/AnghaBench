#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_var_get ; 
 int /*<<< orphan*/  ngx_http_lua_var_set ; 

void
ngx_http_lua_inject_variable_api(lua_State *L)
{
    /* {{{ register reference maps */
    lua_newtable(L);    /* ngx.var */

    lua_createtable(L, 0, 2 /* nrec */); /* metatable for .var */
    lua_pushcfunction(L, ngx_http_lua_var_get);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, ngx_http_lua_var_set);
    lua_setfield(L, -2, "__newindex");
    lua_setmetatable(L, -2);

    lua_setfield(L, -2, "var");
}