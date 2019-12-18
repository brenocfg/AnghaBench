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
struct mp_osd_res {int /*<<< orphan*/  mb; int /*<<< orphan*/  mr; int /*<<< orphan*/  mt; int /*<<< orphan*/  ml; } ;
struct MPContext {int /*<<< orphan*/  osd; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct MPContext* get_mpctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mp_osd_res osd_get_vo_res (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_get_osd_margins(lua_State *L)
{
    struct MPContext *mpctx = get_mpctx(L);
    struct mp_osd_res vo_res = osd_get_vo_res(mpctx->osd);
    lua_pushnumber(L, vo_res.ml);
    lua_pushnumber(L, vo_res.mt);
    lua_pushnumber(L, vo_res.mr);
    lua_pushnumber(L, vo_res.mb);
    return 4;
}