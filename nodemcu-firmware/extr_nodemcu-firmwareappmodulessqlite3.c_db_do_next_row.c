#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_7__ {int has_values; int columns; TYPE_1__* db; int /*<<< orphan*/ * vm; scalar_t__ temp; } ;
typedef  TYPE_2__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  cleanupvm (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_column_name (int /*<<< orphan*/ *,int) ; 
 int sqlite3_data_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int stepvm (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_push_column (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int db_do_next_row(lua_State *L, int packed) {
    int result;
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm;
    int columns;
    int i;

    result = stepvm(L, svm);
    vm = svm->vm; /* stepvm may change svm->vm if re-prepare is needed */
    svm->has_values = result == SQLITE_ROW ? 1 : 0;
    svm->columns = columns = sqlite3_data_count(vm);

    if (result == SQLITE_ROW) {
        if (packed) {
            if (packed == 1) {
                lua_createtable(L, columns, 0);
                for (i = 0; i < columns;) {
                    vm_push_column(L, vm, i);
                    lua_rawseti(L, -2, ++i);
                }
            }
            else {
                lua_createtable(L, 0, columns);
                for (i = 0; i < columns; ++i) {
                    lua_pushstring(L, sqlite3_column_name(vm, i));
                    vm_push_column(L, vm, i);
                    lua_rawset(L, -3);
                }
            }
            return 1;
        }
        else {
            lua_checkstack(L, columns);
            for (i = 0; i < columns; ++i)
                vm_push_column(L, vm, i);
            return svm->columns;
        }
    }

    if (svm->temp) {
        /* finalize and check for errors */
        result = sqlite3_finalize(vm);
        svm->vm = NULL;
        cleanupvm(L, svm);
    }
    else if (result == SQLITE_DONE) {
        result = sqlite3_reset(vm);
    }

    if (result != SQLITE_OK) {
        lua_pushstring(L, sqlite3_errmsg(svm->db->db));
        lua_error(L);
    }
    return 0;
}