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
struct TYPE_17__ {int y; int h; scalar_t__ w; scalar_t__ x; } ;
struct TYPE_16__ {TYPE_2__* panels; } ;
struct TYPE_15__ {TYPE_1__* view; } ;
struct TYPE_14__ {int columnWidth; int n_panels; TYPE_3__** panel; } ;
struct TYPE_13__ {TYPE_6__ pos; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __fix_layout (TYPE_4__*) ; 
 TYPE_3__* __get_panel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_geometry (TYPE_6__*,int,int,int,int) ; 
 int /*<<< orphan*/  __shrink_panels_backward (TYPE_4__*,int) ; 
 int r_cons_get_size (int*) ; 

void __move_panel_to_left(RCore *core, RPanel *panel, int src) {
	RPanels *panels = core->panels;
	__shrink_panels_backward (core, src);
	panels->panel[0] = panel;
	int h, w = r_cons_get_size (&h);
	int p_w = w - panels->columnWidth;
	p_w /= 2;
	int new_w = w - p_w;
	__set_geometry (&panel->view->pos, 0, 1, p_w + 1, h - 1);
	int i = 1;
	for (; i < panels->n_panels; i++) {
		RPanel *tmp = __get_panel (panels, i);
		int t_x = ((double)tmp->view->pos.x / (double)w) * (double)new_w + p_w;
		int t_w = ((double)tmp->view->pos.w / (double)w) * (double)new_w + 1;
		__set_geometry (&tmp->view->pos, t_x, tmp->view->pos.y, t_w, tmp->view->pos.h);
	}
	__fix_layout (core);
	__set_curnode (core, 0);
}