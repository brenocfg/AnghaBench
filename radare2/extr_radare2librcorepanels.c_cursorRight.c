#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_15__ {scalar_t__ offset; scalar_t__ block; int /*<<< orphan*/  assembler; TYPE_2__* print; int /*<<< orphan*/  panels; } ;
struct TYPE_14__ {TYPE_1__* model; } ;
struct TYPE_13__ {int cur; } ;
struct TYPE_12__ {scalar_t__ addr; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPrint ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;
typedef  int /*<<< orphan*/  RAsmOp ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_REGISTERS ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 int R_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cursorThreshold (TYPE_3__*) ; 
 TYPE_3__* getCurPanel (int /*<<< orphan*/ ) ; 
 int r_asm_disassemble (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  r_core_block_read (TYPE_4__*) ; 
 int /*<<< orphan*/  r_core_seek_delta (TYPE_4__*,int) ; 
 int r_print_row_at_off (TYPE_2__*,int) ; 
 scalar_t__ r_print_rowoff (TYPE_2__*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cursorRight(RCore *core) {
	RPanel *cur = getCurPanel (core->panels);
	RPrint *print = core->print;
	if (!strncmp (cur->model->cmd, PANEL_CMD_STACK, strlen (PANEL_CMD_STACK)) && print->cur >= 15) {
		return;
	}
	if (!strncmp (cur->model->cmd, PANEL_CMD_REGISTERS, strlen (PANEL_CMD_REGISTERS))
			|| !strncmp (cur->model->cmd, PANEL_CMD_STACK, strlen (PANEL_CMD_STACK))) {
		print->cur++;
		cur->model->addr++;
	} else {
		print->cur++;
		int threshold = cursorThreshold (cur);
		int row = r_print_row_at_off (print, print->cur);
		if (row >= threshold) {
			core->offset = cur->model->addr;
			RAsmOp op;
			ut32 next_roff = r_print_rowoff (print, row + 1);
			int sz = r_asm_disassemble (core->assembler, &op,
					core->block + next_roff, 32);
			if (sz < 1) {
				sz = 1;
			}
			r_core_seek_delta (core, sz);
			cur->model->addr = core->offset;
			r_core_block_read (core);
			print->cur = R_MAX (print->cur - sz, 0);
		}
	}
}