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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct script_ctx*,char*,char const*) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_loadstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void require(lua_State *L, const char *name)
{
    struct script_ctx *ctx = get_ctx(L);
    MP_DBG(ctx, "loading %s\n", name);
    // Lazy, but better than calling the "require" function manually
    char buf[80];
    snprintf(buf, sizeof(buf), "require '%s'", name);
    if (luaL_loadstring(L, buf))
        lua_error(L);
    lua_call(L, 0, 0);
}