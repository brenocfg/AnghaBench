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
struct script_ctx {int /*<<< orphan*/  log; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int check_loglevel (int /*<<< orphan*/ *,int) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_msg (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static int script_log(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);

    int msgl = check_loglevel(L, 1);

    int last = lua_gettop(L);
    lua_getglobal(L, "tostring"); // args... tostring
    for (int i = 2; i <= last; i++) {
        lua_pushvalue(L, -1); // args... tostring tostring
        lua_pushvalue(L, i); // args... tostring tostring args[i]
        lua_call(L, 1, 1); // args... tostring str
        const char *s = lua_tostring(L, -1);
        if (s == NULL)
            return luaL_error(L, "Invalid argument");
        mp_msg(ctx->log, msgl, "%s%s", s, i > 0 ? " " : "");
        lua_pop(L, 1);  // args... tostring
    }
    mp_msg(ctx->log, msgl, "\n");

    return 0;
}