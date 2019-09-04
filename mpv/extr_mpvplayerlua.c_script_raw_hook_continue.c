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
struct script_ctx {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 int check_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_hook_continue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_raw_hook_continue(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    lua_Integer id = luaL_checkinteger(L, 1);
    return check_error(L, mpv_hook_continue(ctx->client, id));
}