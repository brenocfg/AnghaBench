#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  config; TYPE_3__* panels; } ;
struct TYPE_12__ {TYPE_2__* view; } ;
struct TYPE_11__ {int n_panels; int mouse_on_edge_x; int mouse_orig_x; } ;
struct TYPE_9__ {int const x; } ;
struct TYPE_10__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 TYPE_4__* __get_panel (TYPE_3__*,int) ; 
 scalar_t__ r_config_get_i (int /*<<< orphan*/ ,char*) ; 

bool __check_if_mouse_x_on_edge(RCore *core, int x, int y) {
	RPanels *panels = core->panels;
	const int edge_x = r_config_get_i (core->config, "scr.panelborder")? 3: 1;
	int i = 0;
	for (; i < panels->n_panels; i++) {
		RPanel *panel = __get_panel (panels, i);
		if (x > panel->view->pos.x - (edge_x - 1) && x <= panel->view->pos.x + edge_x) {
			panels->mouse_on_edge_x = true;
			panels->mouse_orig_x = x;
			return true;
		}
	}
	return false;
}