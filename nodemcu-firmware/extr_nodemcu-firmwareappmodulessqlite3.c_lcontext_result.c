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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ lcontext ;

/* Variables and functions */
#define  LUA_TNIL 131 
#define  LUA_TNONE 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 TYPE_1__* lsqlite_checkcontext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_strlen (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lcontext_result(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    switch (lua_type(L, 2)) {
        case LUA_TNUMBER:
#if LUA_VERSION_NUM > 502
            if (lua_isinteger(L, 2))
                sqlite3_result_int64(ctx->ctx, luaL_checkinteger(L, 2));
            else
#endif
            sqlite3_result_double(ctx->ctx, luaL_checknumber(L, 2));
            break;
        case LUA_TSTRING:
            sqlite3_result_text(ctx->ctx, luaL_checkstring(L, 2), lua_strlen(L, 2), SQLITE_TRANSIENT);
            break;
        case LUA_TNIL:
        case LUA_TNONE:
            sqlite3_result_null(ctx->ctx);
            break;
        default:
            luaL_error(L, "invalid result type %s", lua_typename(L, 2));
            break;
    }

    return 0;
}