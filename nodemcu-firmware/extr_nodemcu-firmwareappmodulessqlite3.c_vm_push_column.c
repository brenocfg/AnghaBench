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
 int /*<<< orphan*/  PUSH_INT64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_double (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vm_push_column(lua_State *L, sqlite3_stmt *vm, int idx) {
    switch (sqlite3_column_type(vm, idx)) {
        case SQLITE_INTEGER:
            PUSH_INT64(L, sqlite3_column_int64(vm, idx)
                     , lua_pushlstring(L, (const char*)sqlite3_column_text(vm, idx)
                                        , sqlite3_column_bytes(vm, idx)));
            break;
        case SQLITE_FLOAT:
            lua_pushnumber(L, sqlite3_column_double(vm, idx));
            break;
        case SQLITE_TEXT:
            lua_pushlstring(L, (const char*)sqlite3_column_text(vm, idx), sqlite3_column_bytes(vm, idx));
            break;
        case SQLITE_BLOB:
            lua_pushlstring(L, sqlite3_column_blob(vm, idx), sqlite3_column_bytes(vm, idx));
            break;
        case SQLITE_NULL:
            lua_pushnil(L);
            break;
        default:
            lua_pushnil(L);
            break;
    }
}