#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int printidx; int inc; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  block; int /*<<< orphan*/  assembler; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAsmOp ;

/* Variables and functions */
 int NPF ; 
 int R_ABS (int) ; 
#define  R_CORE_VISUAL_MODE_DB 130 
#define  R_CORE_VISUAL_MODE_PD 129 
#define  R_CORE_VISUAL_MODE_PX 128 
 int /*<<< orphan*/  R_MIN (int,int /*<<< orphan*/ ) ; 
 int r_asm_disassemble (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asm_op_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_asm_op_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setprintmode(RCore *core, int n) {
	RAsmOp op;

	if (n > 0) {
		core->printidx = R_ABS ((core->printidx + 1) % NPF);
	} else {
		if (core->printidx) {
			core->printidx--;
		} else {
			core->printidx = NPF - 1;
		}
	}
	switch (core->printidx) {
	case R_CORE_VISUAL_MODE_PX:
		core->inc = 16;
		break;
	case R_CORE_VISUAL_MODE_PD:
	case R_CORE_VISUAL_MODE_DB:
		r_asm_op_init (&op);
		core->inc = r_asm_disassemble (core->assembler, &op, core->block, R_MIN (32, core->blocksize));
		r_asm_op_fini (&op);
		break;
	}
}