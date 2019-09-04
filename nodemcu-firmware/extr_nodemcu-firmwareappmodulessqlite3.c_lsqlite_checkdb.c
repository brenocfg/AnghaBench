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
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* lsqlite_getdb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static sdb *lsqlite_checkdb(lua_State *L, int index) {
    sdb *db = lsqlite_getdb(L, index);
    if (db->db == NULL) luaL_argerror(L, index, "attempt to use closed sqlite database");
    return db;
}