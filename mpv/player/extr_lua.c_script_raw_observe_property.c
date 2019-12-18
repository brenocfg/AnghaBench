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
typedef  int /*<<< orphan*/  uint64_t ;
struct script_ctx {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  mpv_format ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int check_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_property_format (int /*<<< orphan*/ *,int) ; 
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpv_observe_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_raw_observe_property(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    uint64_t id = luaL_checknumber(L, 1);
    const char *name = luaL_checkstring(L, 2);
    mpv_format format = check_property_format(L, 3);
    return check_error(L, mpv_observe_property(ctx->client, id, name, format));
}