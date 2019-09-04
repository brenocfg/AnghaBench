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
struct TYPE_3__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  c_sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* lsqlite_getdb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int db_tostring(lua_State *L) {
    char buff[32];
    sdb *db = lsqlite_getdb(L, 1);
    if (db->db == NULL)
        strcpy(buff, "closed");
    else
        c_sprintf(buff, "%p", lua_touserdata(L, 1));
    lua_pushfstring(L, "sqlite database (%s)", buff);
    return 1;
}