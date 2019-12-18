#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_3__* panels; } ;
struct TYPE_15__ {TYPE_2__* view; } ;
struct TYPE_14__ {int n_panels; } ;
struct TYPE_12__ {int x; int w; int y; int h; } ;
struct TYPE_13__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;
typedef  int Direction ;

/* Variables and functions */
#define  DOWN 131 
#define  LEFT 130 
#define  RIGHT 129 
#define  UP 128 
 TYPE_4__* __get_cur_panel (TYPE_3__*) ; 
 TYPE_4__* __get_panel (TYPE_3__*,int) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_5__*,int) ; 

bool __move_to_direction(RCore *core, Direction direction) {
	RPanels *panels = core->panels;
	RPanel *cur = __get_cur_panel (panels);
	int cur_x0 = cur->view->pos.x, cur_x1 = cur->view->pos.x + cur->view->pos.w - 1, cur_y0 = cur->view->pos.y, cur_y1 = cur->view->pos.y + cur->view->pos.h - 1;
	int temp_x0, temp_x1, temp_y0, temp_y1;
	int i;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		temp_x0 = p->view->pos.x;
		temp_x1 = p->view->pos.x + p->view->pos.w - 1;
		temp_y0 = p->view->pos.y;
		temp_y1 = p->view->pos.y + p->view->pos.h - 1;
		switch (direction) {
		case LEFT:
			if (temp_x1 == cur_x0) {
				if (temp_y1 <= cur_y0 || cur_y1 <= temp_y0) {
					continue;
				}
				__set_curnode (core, i);
				return true;
			}
			break;
		case RIGHT:
			if (temp_x0 == cur_x1) {
				if (temp_y1 <= cur_y0 || cur_y1 <= temp_y0) {
					continue;
				}
				__set_curnode (core, i);
				return true;
			}
			break;
		case UP:
			if (temp_y1 == cur_y0) {
				if (temp_x1 <= cur_x0 || cur_x1 <= temp_x0) {
					continue;
				}
				__set_curnode (core, i);
				return true;
			}
			break;
		case DOWN:
			if (temp_y0 == cur_y1) {
				if (temp_x1 <= cur_x0 || cur_x1 <= temp_x0) {
					continue;
				}
				__set_curnode (core, i);
				return true;
			}
			break;
		default:
			break;
		}
	}
	return false;
}