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
struct TYPE_4__ {int columns; int /*<<< orphan*/ * vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  dbvm_check_contents (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_push_column (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dbvm_get_uvalues(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = svm->columns;
    int n;
    dbvm_check_contents(L, svm);

    lua_checkstack(L, columns);
    for (n = 0; n < columns; ++n)
        vm_push_column(L, vm, n);
    return columns;
}