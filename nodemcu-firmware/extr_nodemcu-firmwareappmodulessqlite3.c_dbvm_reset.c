#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* db; int /*<<< orphan*/  vm; } ;
typedef  TYPE_2__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 TYPE_2__* lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbvm_reset(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_reset(svm->vm);
    lua_pushinteger(L, sqlite3_errcode(svm->db->db));
    return 1;
}