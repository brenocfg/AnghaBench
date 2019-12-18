#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* view; } ;
struct TYPE_10__ {int n_panels; int /*<<< orphan*/  can; } ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;

/* Variables and functions */
 TYPE_4__* __get_panel (TYPE_3__*,int) ; 
 int /*<<< orphan*/  r_cons_canvas_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  r_cons_canvas_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_flush () ; 

void __panel_all_clear(RPanels *panels) {
	if (!panels) {
		return;
	}
	int i;
	RPanel *panel = NULL;
	for (i = 0; i < panels->n_panels; i++) {
		panel = __get_panel (panels, i);
		r_cons_canvas_fill (panels->can, panel->view->pos.x, panel->view->pos.y, panel->view->pos.w, panel->view->pos.h, ' ');
	}
	r_cons_canvas_print (panels->can);
	r_cons_flush ();
}