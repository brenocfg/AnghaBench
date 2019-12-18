#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_2__* panels; } ;
struct TYPE_25__ {TYPE_1__* model; } ;
struct TYPE_24__ {scalar_t__ mode; int mouse_on_edge_x; int mouse_on_edge_y; } ;
struct TYPE_23__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  title; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int INT8_MAX ; 
 scalar_t__ PANEL_MODE_MENU ; 
 scalar_t__ __check_if_mouse_x_illegal (TYPE_4__*,int) ; 
 int __check_if_mouse_x_on_edge (TYPE_4__*,int,int) ; 
 scalar_t__ __check_if_mouse_y_illegal (TYPE_4__*,int) ; 
 int __check_if_mouse_y_on_edge (TYPE_4__*,int,int) ; 
 scalar_t__ __drag_and_resize (TYPE_4__*) ; 
 TYPE_3__* __get_cur_panel (TYPE_2__*) ; 
 scalar_t__ __handle_mouse_on_X (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  __handle_mouse_on_menu (TYPE_4__*,int,int) ; 
 scalar_t__ __handle_mouse_on_panel (TYPE_4__*,TYPE_3__*,int,int,int*) ; 
 scalar_t__ __handle_mouse_on_top (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  __split_panel_horizontal (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __split_panel_vertical (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_cons_get_click (int*,int*) ; 
 int r_cons_get_size (int*) ; 

bool __handle_mouse(RCore *core, RPanel *panel, int *key) {
	const int MENU_Y = 1;
	RPanels *panels = core->panels;
	if (__drag_and_resize (core)) {
		return true;
	}
	if (*key == 0) {
		int x, y;
		if (r_cons_get_click (&x, &y)) {
			if (y == MENU_Y && __handle_mouse_on_top (core, x, y)) {
				return true;
			}
			if (panels->mode == PANEL_MODE_MENU) {
				__handle_mouse_on_menu (core, x, y);
				return true;
			}
			if (__handle_mouse_on_X (core, x, y)) {
				return true;
			}
			if (__check_if_mouse_x_illegal (core, x) || __check_if_mouse_y_illegal (core, y)) {
				panels->mouse_on_edge_x = false;
				panels->mouse_on_edge_y = false;
				return true;
			}
			panels->mouse_on_edge_x = __check_if_mouse_x_on_edge (core, x, y);
			panels->mouse_on_edge_y = __check_if_mouse_y_on_edge (core, x, y);
			if (panels->mouse_on_edge_x || panels->mouse_on_edge_y) {
				return true;
			}
			if (__handle_mouse_on_panel (core, panel, x, y, key)) {
				return true;
			}
			int h, w = r_cons_get_size (&h);
			if (y == h) {
				RPanel *p = __get_cur_panel (panels);
				__split_panel_horizontal (core, p, p->model->title, p->model->cmd);
			} else if (x == w) {
				RPanel *p = __get_cur_panel (panels);
				__split_panel_vertical (core, p, p->model->title, p->model->cmd);
			}
		} else {
			return false;
		}
	}
	if (*key == INT8_MAX) {
		*key = '"';
		return false;
	}
	return false;
}