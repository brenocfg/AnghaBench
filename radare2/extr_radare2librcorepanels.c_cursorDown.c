#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_8__ {scalar_t__ block; int /*<<< orphan*/  assembler; TYPE_1__* print; int /*<<< orphan*/  panels; } ;
struct TYPE_7__ {int cur; int /*<<< orphan*/  cols; scalar_t__ row_offsets; } ;
typedef  TYPE_1__ RPrint ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  RAsmOp ;

/* Variables and functions */
 int R_MAX (int,int /*<<< orphan*/ ) ; 
 int R_MIN (int,int) ; 
 int cursorThreshold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getCurPanel (int /*<<< orphan*/ ) ; 
 int r_asm_disassemble (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  r_core_seek_delta (TYPE_2__*,int) ; 
 int r_print_row_at_off (TYPE_1__*,int) ; 
 int r_print_rowoff (TYPE_1__*,int) ; 

__attribute__((used)) static void cursorDown(RCore *core) {
	RPanel *cur = getCurPanel (core->panels);
	RPrint *print = core->print;
	ut32 roff, next_roff;
	int row, sz, delta, threshold = cursorThreshold (cur);
	RAsmOp op;
	if (print->row_offsets) {
		row = r_print_row_at_off (print, print->cur);
		roff = r_print_rowoff (print, row);
		if (roff == -1) {
			print->cur++;
			return;
		}
		next_roff = r_print_rowoff (print, row + 1);
		if (next_roff == -1) {
			print->cur++;
			return;
		}
		sz = r_asm_disassemble (core->assembler, &op,
				core->block + next_roff, 32);
		if (sz < 1) {
			sz = 1;
		}
		delta = print->cur - roff;
		print->cur = next_roff + R_MIN (delta, sz - 1);
		row = r_print_row_at_off (print, print->cur);
		if (row >= threshold) {
			r_core_seek_delta (core, sz);
			print->cur = R_MAX (print->cur - sz, 0);
		}
	} else {
		print->cur += R_MAX (1, print->cols);
	}
}