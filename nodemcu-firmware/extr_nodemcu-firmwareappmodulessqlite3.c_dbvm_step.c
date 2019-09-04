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
struct TYPE_4__ {int has_values; int /*<<< orphan*/  vm; int /*<<< orphan*/  columns; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int SQLITE_ROW ; 
 TYPE_1__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_data_count (int /*<<< orphan*/ ) ; 
 int stepvm (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int dbvm_step(lua_State *L) {
    int result;
    sdb_vm *svm = lsqlite_checkvm(L, 1);

    result = stepvm(L, svm);
    svm->has_values = result == SQLITE_ROW ? 1 : 0;
    svm->columns = sqlite3_data_count(svm->vm);

    lua_pushinteger(L, result);
    return 1;
}