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
typedef  int /*<<< orphan*/  sdb_bu ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int cleanupbu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lsqlite_checkbu (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dbbu_finish(lua_State *L) {
    sdb_bu *sbu = lsqlite_checkbu(L, 1);
    return cleanupbu(L, sbu);
}