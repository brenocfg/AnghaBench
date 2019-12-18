#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* print; int /*<<< orphan*/  offset; int /*<<< orphan*/  config; int /*<<< orphan*/ * panels; } ;
struct TYPE_12__ {TYPE_4__* view; TYPE_2__* model; } ;
struct TYPE_8__ {int h; } ;
struct TYPE_11__ {int refresh; int curpos; int sy; int /*<<< orphan*/  sx; TYPE_1__ pos; } ;
struct TYPE_10__ {int /*<<< orphan*/  cur_enabled; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;
typedef  int /*<<< orphan*/  Direction ;

/* Variables and functions */
#define  DOWN 131 
#define  LEFT 130 
#define  RIGHT 129 
#define  UP 128 
 TYPE_5__* __get_cur_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_config_get_i (int /*<<< orphan*/ ,char*) ; 

void __direction_panels_cursor_cb(void *user, int direction) {
	RCore *core = (RCore *)user;
	RPanels *panels = core->panels;
	RPanel *cur = __get_cur_panel (panels);
	cur->view->refresh = true;
	const int THRESHOLD = cur->view->pos.h / 3;
	int sub;
	switch ((Direction)direction) {
	case LEFT:
		if (core->print->cur_enabled) {
			return;
		}
		if (cur->view->sx > 0) {
			cur->view->sx -= r_config_get_i (core->config, "graph.scroll");
		}
		return;
	case RIGHT:
		if (core->print->cur_enabled) {
			return;
		}
		cur->view->sx += r_config_get_i (core->config, "graph.scroll");
		return;
	case UP:
		if (core->print->cur_enabled) {
			if (cur->view->curpos > 0) {
				cur->view->curpos--;
			}
			if (cur->view->sy > 0) {
				sub = cur->view->curpos - cur->view->sy;
				if (sub < 0) {
					cur->view->sy--;
				}
			}
		} else {
			if (cur->view->sy > 0) {
				cur->view->curpos -= 1;
				cur->view->sy -= 1;
			}
		}
		return;
	case DOWN:
		core->offset = cur->model->addr;
		if (core->print->cur_enabled) {
			cur->view->curpos++;
			sub = cur->view->curpos - cur->view->sy;
			if (sub > THRESHOLD) {
				cur->view->sy++;
			}
		} else {
			cur->view->curpos += 1;
			cur->view->sy += 1;
		}
		return;
	}
}