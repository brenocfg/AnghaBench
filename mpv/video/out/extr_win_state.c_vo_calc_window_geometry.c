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
struct vo_win_geometry {int dummy; } ;
struct vo {int dummy; } ;
struct mp_rect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vo_calc_window_geometry2 (struct vo*,struct mp_rect const*,double,struct vo_win_geometry*) ; 

void vo_calc_window_geometry(struct vo *vo, const struct mp_rect *screen,
                             struct vo_win_geometry *out_geo)
{
    vo_calc_window_geometry2(vo, screen, 1.0, out_geo);
}