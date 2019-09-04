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
struct TYPE_7__ {int result_use; int res_use_chain; int op1_use; int op2_use; int op2_use_chain; int op1_use_chain; int result_def; int op1_def; int op2_def; } ;
typedef  TYPE_1__ zend_ssa_op ;
struct TYPE_8__ {int ops; } ;
typedef  TYPE_2__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_NOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  zend_ssa_unlink_use_chain (TYPE_2__*,TYPE_1__*,int) ; 

void zend_ssa_remove_instr(zend_ssa *ssa, zend_op *opline, zend_ssa_op *ssa_op) /* {{{ */
{
	if (ssa_op->result_use >= 0) {
		zend_ssa_unlink_use_chain(ssa, ssa_op - ssa->ops, ssa_op->result_use);
		ssa_op->result_use = -1;
		ssa_op->res_use_chain = -1;
	}
	if (ssa_op->op1_use >= 0) {
		if (ssa_op->op1_use != ssa_op->op2_use) {
			zend_ssa_unlink_use_chain(ssa, ssa_op - ssa->ops, ssa_op->op1_use);
		} else {
			ssa_op->op2_use_chain = ssa_op->op1_use_chain;
		}
		ssa_op->op1_use = -1;
		ssa_op->op1_use_chain = -1;
	}
	if (ssa_op->op2_use >= 0) {
		zend_ssa_unlink_use_chain(ssa, ssa_op - ssa->ops, ssa_op->op2_use);
		ssa_op->op2_use = -1;
		ssa_op->op2_use_chain = -1;
	}

	/* We let the caller make sure that all defs are gone */
	ZEND_ASSERT(ssa_op->result_def == -1);
	ZEND_ASSERT(ssa_op->op1_def == -1);
	ZEND_ASSERT(ssa_op->op2_def == -1);

	MAKE_NOP(opline);
}