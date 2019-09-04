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
struct TYPE_4__ {int /*<<< orphan*/ * vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* lsqlite_getvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static sdb_vm *lsqlite_checkvm(lua_State *L, int index) {
    sdb_vm *svm = lsqlite_getvm(L, index);
    if (svm->vm == NULL) luaL_argerror(L, index, "attempt to use closed sqlite virtual machine");
    return svm;
}