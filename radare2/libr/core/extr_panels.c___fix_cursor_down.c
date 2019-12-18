#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ offset; int /*<<< orphan*/  block; int /*<<< orphan*/  assembler; TYPE_1__* print; } ;
struct TYPE_5__ {scalar_t__ cur; scalar_t__ screen_bounds; int ocur; } ;
typedef  TYPE_1__ RPrint ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  RAsmOp ;

/* Variables and functions */
 void* R_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r_asm_disassemble (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_seek_delta (TYPE_2__*,int) ; 

void __fix_cursor_down(RCore *core) {
	RPrint *print = core->print;
	bool cur_is_visible = core->offset + print->cur + 32 < print->screen_bounds;
	if (!cur_is_visible) {
		int i = 0;
		//XXX: ugly hack
		for (i = 0; i < 2; i++) {
			RAsmOp op;
			int sz = r_asm_disassemble (core->assembler,
					&op, core->block, 32);
			if (sz < 1) {
				sz = 1;
			}
			r_core_seek_delta (core, sz);
			print->cur = R_MAX (print->cur - sz, 0);
			if (print->ocur != -1) {
				print->ocur = R_MAX (print->ocur - sz, 0);
			}
		}
	}
}