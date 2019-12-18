#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int x; int y; int w; int h; } ;
struct TYPE_19__ {int /*<<< orphan*/  offset; TYPE_2__* panels; } ;
struct TYPE_18__ {TYPE_1__* view; } ;
struct TYPE_17__ {int n_panels; } ;
struct TYPE_16__ {TYPE_9__ pos; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_TITLE_DISASSEMBLY ; 
 scalar_t__ __check_panel_type (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* __get_panel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __insert_panel (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_cursor (TYPE_4__*,int) ; 
 int /*<<< orphan*/  __set_geometry (TYPE_9__*,int,int,int,int) ; 
 int /*<<< orphan*/  __set_panel_addr (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_4__*,int,int) ; 

void __update_disassembly_or_open (RCore *core) {
	RPanels *panels = core->panels;
	int i;
	bool create_new = true;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		if (__check_panel_type (p, PANEL_CMD_DISASSEMBLY)) {
			__set_panel_addr (core, p, core->offset);
			create_new = false;
		}
	}
	if (create_new) {
		RPanel *panel = __get_panel (panels, 0);
		int x0 = panel->view->pos.x;
		int y0 = panel->view->pos.y;
		int w0 = panel->view->pos.w;
		int h0 = panel->view->pos.h;
		int threshold_w = x0 + panel->view->pos.w;
		int x1 = x0 + w0 / 2 - 1;
		int w1 = threshold_w - x1;

		__insert_panel (core, 0, PANEL_TITLE_DISASSEMBLY, PANEL_CMD_DISASSEMBLY);
		RPanel *p0 = __get_panel (panels, 0);
		__set_geometry (&p0->view->pos, x0, y0, w0 / 2, h0);

		RPanel *p1 = __get_panel (panels, 1);
		__set_geometry (&p1->view->pos, x1, y0, w1, h0);

		__set_cursor (core, false);
		__set_curnode (core, 0);
	}
	__set_refresh_all (core, false, false);
}