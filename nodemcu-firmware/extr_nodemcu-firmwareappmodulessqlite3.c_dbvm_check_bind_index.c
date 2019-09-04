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
struct TYPE_3__ {int /*<<< orphan*/  vm; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int sqlite3_bind_parameter_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dbvm_check_bind_index(lua_State *L, sdb_vm *svm, int index) {
    if (index < 1 || index > sqlite3_bind_parameter_count(svm->vm)) {
        luaL_error(L, "bind index out of range [1..%d]", sqlite3_bind_parameter_count(svm->vm));
    }
}