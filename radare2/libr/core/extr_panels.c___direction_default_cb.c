#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  panels; } ;
struct TYPE_6__ {TYPE_1__* view; } ;
struct TYPE_5__ {int refresh; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; } ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;
typedef  int /*<<< orphan*/  Direction ;

/* Variables and functions */
#define  DOWN 131 
#define  LEFT 130 
#define  RIGHT 129 
#define  UP 128 
 TYPE_2__* __get_cur_panel (int /*<<< orphan*/ ) ; 

void __direction_default_cb(void *user, int direction) {
	RCore *core = (RCore *)user;
	RPanel *cur = __get_cur_panel (core->panels);
	cur->view->refresh = true;
	switch ((Direction)direction) {
	case LEFT:
		if (cur->view->sx > 0) {
			cur->view->sx--;
		}
		return;
	case RIGHT:
		cur->view->sx++;
		return;
	case UP:
		if (cur->view->sy > 0) {
			cur->view->sy--;
		}
		return;
	case DOWN:
		cur->view->sy++;
		return;
	}
}