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
 int /*<<< orphan*/  cleanupdb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* lsqlite_getdb (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int db_gc(lua_State *L) {
    sdb *db = lsqlite_getdb(L, 1);
    if (db->db != NULL)  /* ignore closed databases */
        cleanupdb(L, db);
    return 0;
}