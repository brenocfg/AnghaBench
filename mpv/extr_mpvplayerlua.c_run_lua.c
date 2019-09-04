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
struct script_ctx {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  MP_FATAL (struct script_ctx*,char*,char const*) ; 
 int /*<<< orphan*/  add_functions (struct script_ctx*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char*** builtin_lua_scripts ; 
 int /*<<< orphan*/  error_handler ; 
 int /*<<< orphan*/  load_builtin ; 
 int /*<<< orphan*/  load_scripts ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct script_ctx*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setglobal (int /*<<< orphan*/ *,char*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 struct script_ctx* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_module_table (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_lua(lua_State *L)
{
    struct script_ctx *ctx = lua_touserdata(L, -1);
    lua_pop(L, 1); // -

    luaL_openlibs(L);

    // used by get_ctx()
    lua_pushlightuserdata(L, ctx); // ctx
    lua_setfield(L, LUA_REGISTRYINDEX, "ctx"); // -

    add_functions(ctx); // mp

    push_module_table(L, "mp"); // mp

    // "mp" is available by default, and no "require 'mp'" is needed
    lua_pushvalue(L, -1); // mp mp
    lua_setglobal(L, "mp"); // mp

    lua_pushstring(L, ctx->name); // mp name
    lua_setfield(L, -2, "script_name"); // mp

    // used by pushnode()
    lua_newtable(L); // mp table
    lua_pushvalue(L, -1); // mp table table
    lua_setfield(L, LUA_REGISTRYINDEX, "UNKNOWN_TYPE"); // mp table
    lua_setfield(L, -2, "UNKNOWN_TYPE"); // mp
    lua_newtable(L); // mp table
    lua_pushvalue(L, -1); // mp table table
    lua_setfield(L, LUA_REGISTRYINDEX, "MAP"); // mp table
    lua_setfield(L, -2, "MAP"); // mp
    lua_newtable(L); // mp table
    lua_pushvalue(L, -1); // mp table table
    lua_setfield(L, LUA_REGISTRYINDEX, "ARRAY"); // mp table
    lua_setfield(L, -2, "ARRAY"); // mp

    lua_pop(L, 1); // -

    assert(lua_gettop(L) == 0);

    // Add a preloader for each builtin Lua module
    lua_getglobal(L, "package"); // package
    assert(lua_type(L, -1) == LUA_TTABLE);
    lua_getfield(L, -1, "preload"); // package preload
    assert(lua_type(L, -1) == LUA_TTABLE);
    for (int n = 0; builtin_lua_scripts[n][0]; n++) {
        lua_pushcfunction(L, load_builtin); // package preload load_builtin
        lua_setfield(L, -2, builtin_lua_scripts[n][0]);
    }
    lua_pop(L, 2); // -

    assert(lua_gettop(L) == 0);

    set_path(L);
    assert(lua_gettop(L) == 0);

    // run this under an error handler that can do backtraces
    lua_pushcfunction(L, error_handler); // errf
    lua_pushcfunction(L, load_scripts); // errf fn
    if (lua_pcall(L, 0, 0, -2)) { // errf [error]
        const char *e = lua_tostring(L, -1);
        MP_FATAL(ctx, "Lua error: %s\n", e ? e : "(unknown)");
    }

    return 0;
}