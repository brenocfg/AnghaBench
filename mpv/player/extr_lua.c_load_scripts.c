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
struct script_ctx {char* filename; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  require (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int load_scripts(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    const char *fname = ctx->filename;

    require(L, "mp.defaults");

    if (fname[0] == '@') {
        require(L, fname);
    } else {
        load_file(L, fname);
    }

    lua_getglobal(L, "mp_event_loop"); // fn
    if (lua_isnil(L, -1))
        luaL_error(L, "no event loop function\n");
    lua_call(L, 0, 0); // -

    return 0;
}