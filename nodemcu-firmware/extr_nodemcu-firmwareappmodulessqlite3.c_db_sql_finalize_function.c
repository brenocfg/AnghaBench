#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_7__ {int /*<<< orphan*/  fn_finalize; TYPE_1__* db; } ;
typedef  TYPE_2__ sdb_func ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  ud; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_3__ lcontext ;
struct TYPE_6__ {int /*<<< orphan*/ * L; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 TYPE_3__* lsqlite_getcontext (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* lsqlite_make_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 void* sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void db_sql_finalize_function(sqlite3_context *context) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(context);
    lua_State *L = func->db->L;
    void *p = sqlite3_aggregate_context(context, 1); /* minimal mem usage */
    lcontext *ctx;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, func->fn_finalize);   /* function to call */

    /* i think it is OK to use assume that using a light user data
    ** as an entry on LUA REGISTRY table will be unique */
    lua_pushlightuserdata(L, p);
    lua_rawget(L, LUA_REGISTRYINDEX);       /* context table */

    if (lua_isnil(L, -1)) { /* not yet created? - shouldn't happen in finalize function */
        lua_pop(L, 1);
        ctx = lsqlite_make_context(L);
        lua_pushlightuserdata(L, p);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }
    else
        ctx = lsqlite_getcontext(L, -1);

    /* set context */
    ctx->ctx = context;

    if (lua_pcall(L, 1, 0, 0)) {
        sqlite3_result_error(context, lua_tostring(L, -1), -1);
    }

    /* invalidate context */
    ctx->ctx = NULL;

    /* cleanup context */
    luaL_unref(L, LUA_REGISTRYINDEX, ctx->ud);
    /* remove it from registry */
    lua_pushlightuserdata(L, p);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    lua_settop(L, top);
}