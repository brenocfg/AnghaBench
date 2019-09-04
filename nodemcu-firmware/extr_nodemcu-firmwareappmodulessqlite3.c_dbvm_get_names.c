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
 TYPE_1__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_column_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbvm_get_names(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_createtable(L, columns, 0);
    for (n = 0; n < columns;) {
        lua_pushstring(L, sqlite3_column_name(vm, n++));
        lua_rawseti(L, -2, n);
    }
    return 1;
}