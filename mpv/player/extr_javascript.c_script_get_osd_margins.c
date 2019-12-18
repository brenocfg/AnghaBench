#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_osd_res {double const ml; double const mt; double const mr; double const mb; } ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {TYPE_1__* mpctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  osd; } ;

/* Variables and functions */
 TYPE_2__* jctx (int /*<<< orphan*/ *) ; 
 struct mp_osd_res osd_get_vo_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_nums_obj (int /*<<< orphan*/ *,char const* const*,double const*) ; 

__attribute__((used)) static void script_get_osd_margins(js_State *J)
{
    struct mp_osd_res r = osd_get_vo_res(jctx(J)->mpctx->osd);
    const char * const names[] = {"left", "top", "right", "bottom", NULL};
    const double vals[] = {r.ml, r.mt, r.mr, r.mb};
    push_nums_obj(J, names, vals);
}