#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct script_ctx {TYPE_1__* mpctx; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  osd; } ;

/* Variables and functions */
 struct script_ctx* get_ctx (int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_1__*) ; 
 int /*<<< orphan*/  osd_set_external (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 

__attribute__((used)) static int script_set_osd_ass(lua_State *L)
{
    struct script_ctx *ctx = get_ctx(L);
    int res_x = luaL_checkinteger(L, 1);
    int res_y = luaL_checkinteger(L, 2);
    const char *text = luaL_checkstring(L, 3);
    if (!text[0])
        text = " "; // force external OSD initialization
    osd_set_external(ctx->mpctx->osd, ctx->client, res_x, res_y, (char *)text);
    mp_wakeup_core(ctx->mpctx);
    return 0;
}