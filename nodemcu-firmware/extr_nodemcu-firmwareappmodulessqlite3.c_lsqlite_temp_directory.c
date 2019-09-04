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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* luaL_optstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 char* sqlite3_temp_directory ; 

__attribute__((used)) static int lsqlite_temp_directory(lua_State *L) {
    const char *oldtemp = sqlite3_temp_directory;

    if (!lua_isnone(L, 1)) {
        const char *temp = luaL_optstring(L, 1, NULL);
        if (sqlite3_temp_directory) {
            sqlite3_free((char*)sqlite3_temp_directory);
        }
        if (temp) {
            sqlite3_temp_directory = sqlite3_mprintf("%s", temp);
        }
        else {
            sqlite3_temp_directory = NULL;
        }
    }
    lua_pushstring(L, oldtemp);
    return 1;
}