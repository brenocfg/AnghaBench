#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 scalar_t__ luaL_dofile (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ luaL_dostring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 TYPE_2__ lua_methods ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lwan_status_error (char*,...) ; 
 int /*<<< orphan*/  request_metatable_name ; 

lua_State *lwan_lua_create_state(const char *script_file, const char *script)
{
    lua_State *L;

    L = luaL_newstate();
    if (UNLIKELY(!L))
        return NULL;

    luaL_openlibs(L);

    luaL_newmetatable(L, request_metatable_name);
    luaL_register(L, NULL, lua_methods.base.base);
    lua_setfield(L, -1, "__index");

    if (script_file) {
        if (UNLIKELY(luaL_dofile(L, script_file) != 0)) {
            lwan_status_error("Error opening Lua script %s: %s", script_file,
                              lua_tostring(L, -1));
            goto close_lua_state;
        }
    } else if (script) {
        if (UNLIKELY(luaL_dostring(L, script) != 0)) {
            lwan_status_error("Error evaluating Lua script %s",
                              lua_tostring(L, -1));
            goto close_lua_state;
        }
    } else {
        lwan_status_error("Either file or inline script has to be provided");
        goto close_lua_state;
    }

    return L;

close_lua_state:
    lua_close(L);
    return NULL;
}