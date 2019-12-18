#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct Getarg {int /*<<< orphan*/ * insn; } ;
struct TYPE_4__ {scalar_t__ base; scalar_t__ disp; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  imm; TYPE_1__ mem; scalar_t__ reg; } ;
typedef  TYPE_2__ cs_ppc_op ;
typedef  int /*<<< orphan*/  cs_insn ;

/* Variables and functions */
 TYPE_2__ INSOP (int) ; 
#define  PPC_OP_CRX 132 
#define  PPC_OP_IMM 131 
#define  PPC_OP_INVALID 130 
#define  PPC_OP_MEM 129 
#define  PPC_OP_REG 128 

__attribute__((used)) static ut64 getarg(struct Getarg *gop, int n) {
	ut64 value = 0;
	cs_insn *insn = gop->insn;
	cs_ppc_op op;

	if (n < 0 || n >= 8) {
		return 0;
	}

	op = INSOP (n);
	switch (op.type) {
	case PPC_OP_INVALID:
		break;
	case PPC_OP_REG:
		value = op.reg;
		break;
	case PPC_OP_IMM:
		value = (ut64) op.imm;
		break;
	case PPC_OP_MEM:
		value = op.mem.disp + op.mem.base;
		break;
	case PPC_OP_CRX: // Condition Register field
		value = (ut64) op.imm;
		break;
	}
	return value;
}