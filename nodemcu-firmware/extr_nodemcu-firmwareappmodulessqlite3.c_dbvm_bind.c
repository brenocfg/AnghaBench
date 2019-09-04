#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_4__ {int /*<<< orphan*/ * vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int dbvm_bind_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dbvm_check_bind_index (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dbvm_bind(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int index = luaL_checkint(L, 2);
    int result;

    dbvm_check_bind_index(L, svm, index);
    result = dbvm_bind_index(L, vm, index, 3);

    lua_pushinteger(L, result);
    return 1;
}