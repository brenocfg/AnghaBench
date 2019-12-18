#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ op1_def; scalar_t__ op2_def; scalar_t__ result_def; } ;
typedef  TYPE_1__ zend_ssa_op ;
typedef  int /*<<< orphan*/  zend_ssa ;

/* Variables and functions */
 int /*<<< orphan*/  zend_ssa_remove_op1_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ssa_remove_op2_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ssa_remove_result_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ssa_remove_uses_of_var (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void zend_ssa_remove_defs_of_instr(zend_ssa *ssa, zend_ssa_op *ssa_op) /* {{{ */
{
	if (ssa_op->op1_def >= 0) {
		zend_ssa_remove_uses_of_var(ssa, ssa_op->op1_def);
		zend_ssa_remove_op1_def(ssa, ssa_op);
	}
	if (ssa_op->op2_def >= 0) {
		zend_ssa_remove_uses_of_var(ssa, ssa_op->op2_def);
		zend_ssa_remove_op2_def(ssa, ssa_op);
	}
	if (ssa_op->result_def >= 0) {
		zend_ssa_remove_uses_of_var(ssa, ssa_op->result_def);
		zend_ssa_remove_result_def(ssa, ssa_op);
	}
}