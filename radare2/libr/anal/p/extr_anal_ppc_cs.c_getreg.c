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
struct Getarg {int /*<<< orphan*/  handle; int /*<<< orphan*/ * insn; } ;
typedef  int /*<<< orphan*/  csh ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_5__ {int type; TYPE_1__ mem; int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ cs_ppc_op ;
typedef  int /*<<< orphan*/  cs_insn ;

/* Variables and functions */
 TYPE_2__ INSOP (int) ; 
#define  PPC_OP_CRX 132 
#define  PPC_OP_IMM 131 
#define  PPC_OP_INVALID 130 
#define  PPC_OP_MEM 129 
#define  PPC_OP_REG 128 
 char const* cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *getreg(struct Getarg *gop, int n) {
	cs_insn *insn = gop->insn;
	csh handle = gop->handle;

	if (n < 0 || n >= 8) {
		return NULL;
	}
	cs_ppc_op op = INSOP (n);
	switch (op.type) {
	case PPC_OP_REG:
		return cs_reg_name (handle, op.reg);
	case PPC_OP_MEM:
		return cs_reg_name (handle, op.mem.base);
	case PPC_OP_INVALID:
	case PPC_OP_IMM:
	case PPC_OP_CRX: // Condition Register field
		return NULL;
	}
	return NULL;
}