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
typedef  int /*<<< orphan*/  sqlite3_value ;
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
 char const* sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void db_push_value(lua_State *L, sqlite3_value *value) {
    switch (sqlite3_value_type(value)) {
        case SQLITE_TEXT:
            lua_pushlstring(L, (const char*)sqlite3_value_text(value), sqlite3_value_bytes(value));
            break;

        case SQLITE_INTEGER:
            PUSH_INT64(L, sqlite3_value_int64(value)
                        , lua_pushlstring(L, (const char*)sqlite3_value_text(value)
                                            , sqlite3_value_bytes(value)));
            break;

        case SQLITE_FLOAT:
            lua_pushnumber(L, sqlite3_value_double(value));
            break;

        case SQLITE_BLOB:
            lua_pushlstring(L, sqlite3_value_blob(value), sqlite3_value_bytes(value));
            break;

        case SQLITE_NULL:
            lua_pushnil(L);
            break;

        default:
            /* things done properly (SQLite + Lua SQLite)
            ** this should never happen */
            lua_pushnil(L);
            break;
    }
}