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
 int /*<<< orphan*/  MP_DBG (struct script_ctx*,char*,char const*) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int luaL_loadfile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_file(lua_State *L, const char *fname)
{
    struct script_ctx *ctx = get_ctx(L);
    MP_DBG(ctx, "loading file %s\n", fname);
    int r = luaL_loadfile(L, fname);
    if (r)
        lua_error(L);
    lua_call(L, 0, 0);
}