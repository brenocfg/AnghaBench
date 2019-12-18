#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* panels; } ;
struct TYPE_7__ {int mouse_on_edge_x; int mouse_on_edge_y; scalar_t__ mouse_orig_y; scalar_t__ mouse_orig_x; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __set_refresh_all (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  __update_edge_x (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  __update_edge_y (TYPE_2__*,scalar_t__) ; 
 scalar_t__ r_cons_get_click (int*,int*) ; 

bool __drag_and_resize(RCore *core) {
	RPanels *panels = core->panels;
	if (panels->mouse_on_edge_x || panels->mouse_on_edge_y) {
		int x, y;
		if (r_cons_get_click (&x, &y)) {
			if (panels->mouse_on_edge_x) {
				__update_edge_x (core, x - panels->mouse_orig_x);
			}
			if (panels->mouse_on_edge_y) {
				__update_edge_y (core, y - panels->mouse_orig_y);
			}
			__set_refresh_all (core, false, false);
		}
		panels->mouse_on_edge_x = false;
		panels->mouse_on_edge_y = false;
		return true;
	}
	return false;
}