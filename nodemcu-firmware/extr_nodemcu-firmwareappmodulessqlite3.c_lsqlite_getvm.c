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
typedef  int /*<<< orphan*/  sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite_vm_meta ; 

__attribute__((used)) static sdb_vm *lsqlite_getvm(lua_State *L, int index) {
    sdb_vm *svm = (sdb_vm*)luaL_checkudata(L, index, sqlite_vm_meta);
    if (svm == NULL) luaL_argerror(L, index, "bad sqlite virtual machine");
    return svm;
}