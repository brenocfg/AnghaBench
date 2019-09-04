#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; scalar_t__ reg; scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ reg; } ;
struct stack_op {TYPE_2__ src; TYPE_1__ dest; } ;
struct instruction {struct stack_op stack_op; } ;
struct cfi_reg {scalar_t__ base; int offset; } ;
struct insn_state {struct cfi_reg cfa; } ;

/* Variables and functions */
 scalar_t__ CFI_SP ; 
 scalar_t__ OP_DEST_PUSH ; 
 scalar_t__ OP_DEST_REG ; 
 scalar_t__ OP_SRC_ADD ; 
 scalar_t__ OP_SRC_POP ; 

__attribute__((used)) static int update_insn_state_regs(struct instruction *insn, struct insn_state *state)
{
	struct cfi_reg *cfa = &state->cfa;
	struct stack_op *op = &insn->stack_op;

	if (cfa->base != CFI_SP)
		return 0;

	/* push */
	if (op->dest.type == OP_DEST_PUSH)
		cfa->offset += 8;

	/* pop */
	if (op->src.type == OP_SRC_POP)
		cfa->offset -= 8;

	/* add immediate to sp */
	if (op->dest.type == OP_DEST_REG && op->src.type == OP_SRC_ADD &&
	    op->dest.reg == CFI_SP && op->src.reg == CFI_SP)
		cfa->offset -= op->src.offset;

	return 0;
}