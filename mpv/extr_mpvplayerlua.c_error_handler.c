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
struct script_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct script_ctx*,char*,char const*) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_loadstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int error_handler(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);

    if (luaL_loadstring(L, "return debug.traceback('', 3)") == 0) { // e fn|err
        lua_call(L, 0, 1); // e backtrace
        const char *tr = lua_tostring(L, -1);
        MP_WARN(ctx, "%s\n", tr ? tr : "(unknown)");
    }
    lua_pop(L, 1); // e

    return 1;
}