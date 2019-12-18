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
struct TYPE_13__ {TYPE_3__* panels; } ;
struct TYPE_12__ {TYPE_2__* view; } ;
struct TYPE_11__ {int n_panels; } ;
struct TYPE_9__ {scalar_t__ x; int w; } ;
struct TYPE_10__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int PANEL_CONFIG_SIDEPANEL_W ; 
 TYPE_4__* __get_panel (TYPE_3__*,int) ; 
 int /*<<< orphan*/  r_cons_get_size (int*) ; 

void __adjust_side_panels(RCore *core) {
	int i, h;
	(void)r_cons_get_size (&h);
	RPanels *panels = core->panels;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		if (p->view->pos.x == 0) {
			if (p->view->pos.w >= PANEL_CONFIG_SIDEPANEL_W) {
				p->view->pos.x += PANEL_CONFIG_SIDEPANEL_W - 1;
				p->view->pos.w -= PANEL_CONFIG_SIDEPANEL_W - 1;
			}
		}
	}
}