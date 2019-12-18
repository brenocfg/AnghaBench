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
struct TYPE_13__ {scalar_t__ w; scalar_t__ h; } ;
struct TYPE_12__ {TYPE_2__* view; } ;
struct TYPE_11__ {int n_panels; TYPE_5__* can; } ;
struct TYPE_9__ {scalar_t__ x; int w; scalar_t__ y; int h; } ;
struct TYPE_10__ {int edgeflag; int refresh; TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RConsCanvas ;

/* Variables and functions */
 int PANEL_EDGE_BOTTOM ; 
 int PANEL_EDGE_RIGHT ; 
 TYPE_4__* __get_panel (TYPE_3__*,int) ; 

void __fit_to_canvas(RPanels *panels) {
	RConsCanvas *can = panels->can;
	int i, w, h;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *panel = __get_panel (panels, i);
		if (!panel) {
			continue;
		}
		if (panel->view->edgeflag & 1 << PANEL_EDGE_RIGHT && panel->view->pos.x < can->w) {
			w = can->w - panel->view->pos.x;
			if (w != panel->view->pos.w) {
				panel->view->pos.w = w;
				panel->view->refresh = true;
			}
		}
		if (panel->view->edgeflag & 1 << PANEL_EDGE_BOTTOM && panel->view->pos.y < can->h) {
			h = can->h - panel->view->pos.y;
			if (h != panel->view->pos.h) {
				panel->view->pos.h = h;
				panel->view->refresh = true;
			}
		}
	}
}