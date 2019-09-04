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
struct mp_osd_res {double w; double h; int display_par; } ;
struct MPContext {int /*<<< orphan*/  osd; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 double MPMAX (double,int) ; 
 struct MPContext* get_mpctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 struct mp_osd_res osd_get_vo_res (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_get_osd_size(lua_State *L)
{
    struct MPContext *mpctx = get_mpctx(L);
    struct mp_osd_res vo_res = osd_get_vo_res(mpctx->osd);
    double aspect = 1.0 * vo_res.w / MPMAX(vo_res.h, 1) /
                    (vo_res.display_par ? vo_res.display_par : 1);
    lua_pushnumber(L, vo_res.w);
    lua_pushnumber(L, vo_res.h);
    lua_pushnumber(L, aspect);
    return 3;
}