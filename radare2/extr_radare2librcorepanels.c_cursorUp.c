#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct TYPE_14__ {scalar_t__ offset; int /*<<< orphan*/  panels; TYPE_2__* print; } ;
struct TYPE_13__ {TYPE_1__* model; } ;
struct TYPE_12__ {scalar_t__ cur; int cols; scalar_t__ row_offsets; } ;
struct TYPE_11__ {scalar_t__ addr; } ;
typedef  TYPE_2__ RPrint ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 void* R_MIN (scalar_t__,int) ; 
 scalar_t__ UT32_MAX ; 
 TYPE_3__* getCurPanel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_seek_delta (TYPE_4__*,int) ; 
 int /*<<< orphan*/  r_core_visual_disasm_up (TYPE_4__*,int*) ; 
 int r_print_row_at_off (TYPE_2__*,scalar_t__) ; 
 scalar_t__ r_print_rowoff (TYPE_2__*,int) ; 

__attribute__((used)) static void cursorUp(RCore *core) {
	RPrint *print = core->print;
	ut32 roff;
	int row;
	if (print->row_offsets) {
		row = r_print_row_at_off (print, print->cur);
		roff = r_print_rowoff (print, row);
		if (roff == UT32_MAX) {
			print->cur--;
			return;
		}
		if (row > 0) {
			ut32 prev_roff;
			int delta, prev_sz;
			prev_roff = r_print_rowoff (print, row - 1);
			delta = print->cur - roff;
			prev_sz = roff - prev_roff;
			int res = R_MIN (delta, prev_sz - 1);
			ut64 cur = prev_roff + res;
			if (cur == print->cur) {
				if (print->cur > 0) {
					print->cur--;
				}
			} else {
				print->cur = prev_roff + delta;
			}
		} else {
			RPanel *cur = getCurPanel (core->panels);
			int cols = print->cols;
			ut64 prevoff = core->offset;
			r_core_visual_disasm_up (core, &cols);
			r_core_seek_delta (core, -cols);
			cur->model->addr = core->offset;
			print->cur = R_MIN (prevoff - core->offset - 1, print->cur);
		}
	} else {
		print->cur -= print->cols;
	}
}