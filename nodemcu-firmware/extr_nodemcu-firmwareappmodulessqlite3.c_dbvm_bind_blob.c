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
struct TYPE_3__ {int /*<<< orphan*/  vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 TYPE_1__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lua_strlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ ,int,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbvm_bind_blob(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checkint(L, 2);
    const char *value = luaL_checkstring(L, 3);
    int len = lua_strlen(L, 3);

    lua_pushinteger(L, sqlite3_bind_blob(svm->vm, index, value, len, SQLITE_TRANSIENT));
    return 1;
}