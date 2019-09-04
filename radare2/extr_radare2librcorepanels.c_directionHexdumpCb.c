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
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* print; int /*<<< orphan*/  config; int /*<<< orphan*/ * panels; } ;
struct TYPE_16__ {TYPE_4__* view; TYPE_3__* model; } ;
struct TYPE_13__ {int /*<<< orphan*/  h; } ;
struct TYPE_15__ {int refresh; int /*<<< orphan*/  sy; TYPE_2__ pos; int /*<<< orphan*/  sx; } ;
struct TYPE_14__ {int addr; int /*<<< orphan*/  cache; } ;
struct TYPE_12__ {int cur; int /*<<< orphan*/  cur_enabled; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;
typedef  int /*<<< orphan*/  Direction ;

/* Variables and functions */
#define  DOWN 131 
#define  LEFT 130 
#define  RIGHT 129 
#define  UP 128 
 int /*<<< orphan*/  cursorDown (TYPE_6__*) ; 
 int /*<<< orphan*/  cursorLeft (TYPE_6__*) ; 
 int /*<<< orphan*/  cursorRight (TYPE_6__*) ; 
 int /*<<< orphan*/  cursorUp (TYPE_6__*) ; 
 TYPE_5__* getCurPanel (int /*<<< orphan*/ *) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void directionHexdumpCb(void *user, int direction) {
	RCore *core = (RCore *)user;
	RPanels *panels = core->panels;
	RPanel *cur = getCurPanel (panels);
	int cols = r_config_get_i (core->config, "hex.cols");
	if (cols < 1) {
		cols = 16;
	}
	cur->view->refresh = true;
	switch ((Direction)direction) {
	case LEFT:
		if (!core->print->cur) {
			cur->model->addr -= cols;
			core->print->cur += cols - 1;
		} else if (core->print->cur_enabled) {
			cursorLeft (core);
		} else if (cur->view->sx > 0) {
			cur->view->sx--;
			cur->view->refresh = true;
		}
		return;
	case RIGHT:
		if (core->print->cur / cols + 1 > cur->view->pos.h - 5
				&& core->print->cur % cols == cols - 1) {
			cur->model->addr += cols;
			core->print->cur -= cols - 1;
		} else if (core->print->cur_enabled) {
			cursorRight (core);
		} else {
			cur->view->sx++;
			cur->view->refresh = true;
		}
		return;
	case UP:
		if (!cur->model->cache) {
			if (core->print->cur_enabled) {
				if (!(core->print->cur / cols)) {
					cur->model->addr -= cols;
				} else {
					cursorUp (core);
				}
			} else {
				if (cur->model->addr <= cols) {
					cur->model->addr = 0;
				} else {
					cur->model->addr -= cols;
				}
			}
		} else if (cur->view->sy > 0) {
			cur->view->sy--;
		}
		return;
	case DOWN:
		if (!cur->model->cache) {
			if (core->print->cur_enabled) {
				if (core->print->cur / cols + 1 > cur->view->pos.h - 5) {
					cur->model->addr += cols;
				} else {
					cursorDown (core);
				}
			} else {
				cur->model->addr += cols;
			}
		} else {
			cur->view->sy++;
		}
		return;
	}
}