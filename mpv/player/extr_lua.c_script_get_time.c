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

/* Variables and functions */
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 double mpv_get_time_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_get_time(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    lua_pushnumber(L, mpv_get_time_us(ctx->client) / (double)(1000 * 1000));
    return 1;
}