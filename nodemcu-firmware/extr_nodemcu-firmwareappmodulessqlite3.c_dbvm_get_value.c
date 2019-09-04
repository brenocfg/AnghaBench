#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  dbvm_check_contents (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dbvm_check_index (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_push_column (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dbvm_get_value(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checkint(L, 2);
    dbvm_check_contents(L, svm);
    dbvm_check_index(L, svm, index);
    vm_push_column(L, svm->vm, index);
    return 1;
}