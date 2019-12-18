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
struct TYPE_9__ {int x; int w; int y; int h; } ;
struct TYPE_10__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 TYPE_4__* __get_panel (TYPE_3__*,int) ; 

int __get_panel_idx_in_pos(RCore *core, int x, int y) {
	RPanels *panels = core->panels;
	int i = -1;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		if (x >= p->view->pos.x && x < p->view->pos.x + p->view->pos.w) {
			if (y >= p->view->pos.y && y < p->view->pos.y + p->view->pos.h) {
				break;
			}
		}
	}
	return i;
}