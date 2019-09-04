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
struct TYPE_2__ {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
struct vo_win_geometry {int /*<<< orphan*/  monitor_par; TYPE_1__ win; } ;
struct vo {int /*<<< orphan*/  monitor_par; scalar_t__ dheight; scalar_t__ dwidth; } ;

/* Variables and functions */

void vo_apply_window_geometry(struct vo *vo, const struct vo_win_geometry *geo)
{
    vo->dwidth = geo->win.x1 - geo->win.x0;
    vo->dheight = geo->win.y1 - geo->win.y0;
    vo->monitor_par = geo->monitor_par;
}