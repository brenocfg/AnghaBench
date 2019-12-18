#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int w; int /*<<< orphan*/  x; scalar_t__ h; scalar_t__ y; } ;
struct TYPE_16__ {TYPE_2__* panels; } ;
struct TYPE_15__ {TYPE_1__* view; } ;
struct TYPE_14__ {int n_panels; TYPE_3__** panel; } ;
struct TYPE_13__ {TYPE_6__ pos; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __fix_layout (TYPE_4__*) ; 
 TYPE_3__* __get_panel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_geometry (TYPE_6__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  __shrink_panels_backward (TYPE_4__*,int) ; 
 int r_cons_get_size (int*) ; 

void __move_panel_to_up(RCore *core, RPanel *panel, int src) {
	RPanels *panels = core->panels;
	__shrink_panels_backward (core, src);
	panels->panel[0] = panel;
	int h, w = r_cons_get_size (&h);
	int p_h = h / 2;
	int new_h = h - p_h;
	__set_geometry (&panel->view->pos, 0, 1, w, p_h - 1);
	int i = 1;
	for (; i < panels->n_panels; i++) {
		RPanel *tmp = __get_panel (panels, i);
		int t_y = ((double)tmp->view->pos.y / (double)h) * (double)new_h + p_h;
		int t_h = ((double)tmp->view->pos.h / (double)h) * (double)new_h + 1;
		__set_geometry (&tmp->view->pos, tmp->view->pos.x, t_y, tmp->view->pos.w, t_h);
	}
	__fix_layout (core);
	__set_curnode (core, 0);
}