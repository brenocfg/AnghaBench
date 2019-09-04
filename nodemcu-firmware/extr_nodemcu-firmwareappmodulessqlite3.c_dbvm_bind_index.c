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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TBOOLEAN 132 
#define  LUA_TNIL 131 
#define  LUA_TNONE 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int SQLITE_MISUSE ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_strlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int sqlite3_bind_double (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbvm_bind_index(lua_State *L, sqlite3_stmt *vm, int index, int lindex) {
    switch (lua_type(L, lindex)) {
        case LUA_TSTRING:
            return sqlite3_bind_text(vm, index, lua_tostring(L, lindex), lua_strlen(L, lindex), SQLITE_TRANSIENT);
        case LUA_TNUMBER:
#if LUA_VERSION_NUM > 502
            if (lua_isinteger(L, lindex))
                return sqlite3_bind_int64(vm, index, lua_tointeger(L, lindex));
#endif
            return sqlite3_bind_double(vm, index, lua_tonumber(L, lindex));
        case LUA_TBOOLEAN:
            return sqlite3_bind_int(vm, index, lua_toboolean(L, lindex) ? 1 : 0);
        case LUA_TNONE:
        case LUA_TNIL:
            return sqlite3_bind_null(vm, index);
        default:
            luaL_error(L, "index (%d) - invalid data type for bind (%s)", index, lua_typename(L, lua_type(L, lindex)));
            return SQLITE_MISUSE; /*!*/
    }
}