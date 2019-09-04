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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int /*<<< orphan*/ * vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int SQLITE_OK ; 
 int dbvm_bind_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int sqlite3_bind_parameter_count (int /*<<< orphan*/ *) ; 
 char* sqlite3_bind_parameter_name (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dbvm_bind_names(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int count = sqlite3_bind_parameter_count(vm);
    const char *name;
    int result, n;
    luaL_checktype(L, 2, LUA_TTABLE);

    for (n = 1; n <= count; ++n) {
        name = sqlite3_bind_parameter_name(vm, n);
        if (name && (name[0] == ':' || name[0] == '$')) {
            lua_pushstring(L, ++name);
            lua_gettable(L, 2);
            result = dbvm_bind_index(L, vm, n, -1);
            lua_pop(L, 1);
        }
        else {
            lua_pushinteger(L, n);
            lua_gettable(L, 2);
            result = dbvm_bind_index(L, vm, n, -1);
            lua_pop(L, 1);
        }

        if (result != SQLITE_OK) {
            lua_pushinteger(L, result);
            return 1;
        }
    }

    lua_pushinteger(L, SQLITE_OK);
    return 1;
}