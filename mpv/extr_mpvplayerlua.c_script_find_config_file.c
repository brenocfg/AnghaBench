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
struct MPContext {int /*<<< orphan*/  global; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct MPContext* get_mpctx (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* mp_find_config_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int script_find_config_file(lua_State *L)
{
    struct MPContext *mpctx = get_mpctx(L);
    const char *s = luaL_checkstring(L, 1);
    char *path = mp_find_config_file(NULL, mpctx->global, s);
    if (path) {
        lua_pushstring(L, path);
    } else {
        lua_pushnil(L);
    }
    talloc_free(path);
    return 1;
}