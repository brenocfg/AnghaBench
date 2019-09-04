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
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* mp_path_join (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int script_join_path(lua_State *L)
{
    const char *p1 = luaL_checkstring(L, 1);
    const char *p2 = luaL_checkstring(L, 2);
    char *r = mp_path_join(NULL, p1, p2);
    lua_pushstring(L, r);
    talloc_free(r);
    return 1;
}