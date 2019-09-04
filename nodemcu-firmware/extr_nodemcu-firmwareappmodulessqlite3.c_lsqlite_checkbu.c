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
struct TYPE_4__ {int /*<<< orphan*/ * bu; } ;
typedef  TYPE_1__ sdb_bu ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* lsqlite_getbu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static sdb_bu *lsqlite_checkbu(lua_State *L, int index) {
    sdb_bu *sbu = lsqlite_getbu(L, index);
    if (sbu->bu == NULL) luaL_argerror(L, index, "attempt to use closed sqlite database backup");
    return sbu;
}