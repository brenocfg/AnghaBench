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
 int cleanupvm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lsqlite_checkvm (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dbvm_finalize(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    return cleanupvm(L, svm);
}