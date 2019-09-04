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
typedef  void* uint64_t ;
struct script_ctx {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int check_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_hook_add (int /*<<< orphan*/ ,void*,char const*,int) ; 

__attribute__((used)) static int script_raw_hook_add(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    uint64_t ud = luaL_checkinteger(L, 1);
    const char *name = luaL_checkstring(L, 2);
    int pri = luaL_checkinteger(L, 3);
    return check_error(L, mpv_hook_add(ctx->client, ud, name, pri));
}