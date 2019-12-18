#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* print; int /*<<< orphan*/  panels; } ;
struct TYPE_11__ {TYPE_1__* model; } ;
struct TYPE_10__ {int cur; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_2__ RPrint ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_REGISTERS ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 scalar_t__ __check_panel_type (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fix_cursor_down (TYPE_4__*) ; 
 TYPE_3__* __get_cur_panel (int /*<<< orphan*/ ) ; 

void __cursor_right(RCore *core) {
	RPanel *cur = __get_cur_panel (core->panels);
	RPrint *print = core->print;
	if (__check_panel_type (cur, PANEL_CMD_STACK) && print->cur >= 15) {
		return;
	}
	if (__check_panel_type (cur, PANEL_CMD_REGISTERS)
			|| __check_panel_type (cur, PANEL_CMD_STACK)) {
		print->cur++;
		cur->model->addr++;
	} else if (__check_panel_type (cur, PANEL_CMD_DISASSEMBLY)) {
		print->cur++;
		__fix_cursor_down (core);
	} else {
		print->cur++;
	}
}