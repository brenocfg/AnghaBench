#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_13__ {scalar_t__ offset; TYPE_2__* print; int /*<<< orphan*/  panels; } ;
struct TYPE_12__ {TYPE_1__* model; } ;
struct TYPE_11__ {scalar_t__ cur; int cols; } ;
struct TYPE_10__ {scalar_t__ addr; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPrint ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_REGISTERS ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 TYPE_3__* getCurPanel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_seek_delta (TYPE_4__*,int) ; 
 int /*<<< orphan*/  r_core_visual_disasm_up (TYPE_4__*,int*) ; 
 int r_print_row_at_off (TYPE_2__*,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cursorLeft(RCore *core) {
	RPanel *cur = getCurPanel (core->panels);
	RPrint *print = core->print;
	if (!strncmp (cur->model->cmd, PANEL_CMD_REGISTERS, strlen (PANEL_CMD_REGISTERS))
			|| !strncmp (cur->model->cmd, PANEL_CMD_STACK, strlen (PANEL_CMD_STACK))) {
		if (print->cur > 0) {
			print->cur--;
			cur->model->addr--;
		}
	} else if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
					strcmp (cur->model->cmd, "pdc")) {
		print->cur--;
		int row = r_print_row_at_off (print, print->cur);
		if (row < 0) {
			int cols = print->cols;
			ut64 prevoff = core->offset;
			core->offset = cur->model->addr;
			r_core_visual_disasm_up (core, &cols);
			r_core_seek_delta (core, -cols);
			cur->model->addr = core->offset;
			print->cur = prevoff - core->offset - 1;
		}
	} else {
		print->cur--;
	}
}