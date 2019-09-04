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
struct TYPE_3__ {int /*<<< orphan*/ * vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* lsqlite_getvm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dbvm_isopen(lua_State *L) {
    sdb_vm *svm = lsqlite_getvm(L, 1);
    lua_pushboolean(L, svm->vm != NULL ? 1 : 0);
    return 1;
}