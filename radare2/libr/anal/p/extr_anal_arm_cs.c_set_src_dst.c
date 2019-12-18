#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_insn ;
struct TYPE_10__ {int /*<<< orphan*/  disp; int /*<<< orphan*/  scale; } ;
struct TYPE_11__ {int type; TYPE_2__ mem; } ;
typedef  TYPE_3__ cs_arm_op ;
struct TYPE_9__ {int /*<<< orphan*/  disp; } ;
struct TYPE_12__ {TYPE_1__ mem; } ;
typedef  TYPE_4__ cs_arm64_op ;
struct TYPE_13__ {int /*<<< orphan*/ * reg; int /*<<< orphan*/ * regdelta; int /*<<< orphan*/  delta; int /*<<< orphan*/  mul; } ;
typedef  TYPE_5__ RAnalValue ;

/* Variables and functions */
#define  ARM_OP_MEM 129 
#define  ARM_OP_REG 128 
 TYPE_3__ INSOP (int) ; 
 TYPE_4__ INSOP64 (int) ; 
 int /*<<< orphan*/ * base_regs ; 
 int /*<<< orphan*/  parse_reg64_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_reg_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * regdelta_regs ; 

__attribute__((used)) static void set_src_dst(RAnalValue *val, csh *handle, cs_insn *insn, int x, int bits) {
	cs_arm_op armop = INSOP (x);
	cs_arm64_op arm64op = INSOP64 (x);
	if (bits == 64) {
		parse_reg64_name (&base_regs[x], &regdelta_regs[x], *handle, insn, x);
	} else {
		parse_reg_name (&base_regs[x], &regdelta_regs[x], *handle, insn, x);
	}
	switch (armop.type) {
	case ARM_OP_REG:
		break;
	case ARM_OP_MEM:
		if (bits == 64) {
			val->delta = arm64op.mem.disp;
		} else {
			val->mul = armop.mem.scale;
			val->delta = armop.mem.disp;
		}
		val->regdelta = &regdelta_regs[x];
		break;
	default:
		break;
	}
	val->reg = &base_regs[x];
}