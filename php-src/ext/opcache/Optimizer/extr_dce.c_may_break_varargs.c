#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t op1_def; size_t op2_def; size_t result_def; } ;
typedef  TYPE_2__ zend_ssa_op ;
struct TYPE_10__ {TYPE_1__* vars; } ;
typedef  TYPE_3__ zend_ssa ;
struct TYPE_11__ {scalar_t__ num_args; } ;
typedef  TYPE_4__ zend_op_array ;
typedef  int zend_bool ;
struct TYPE_8__ {scalar_t__ var; } ;

/* Variables and functions */

__attribute__((used)) static inline zend_bool may_break_varargs(const zend_op_array *op_array, const zend_ssa *ssa, const zend_ssa_op *ssa_op) {
	if (ssa_op->op1_def >= 0
			&& ssa->vars[ssa_op->op1_def].var < op_array->num_args) {
		return 1;
	}
	if (ssa_op->op2_def >= 0
			&& ssa->vars[ssa_op->op2_def].var < op_array->num_args) {
		return 1;
	}
	if (ssa_op->result_def >= 0
			&& ssa->vars[ssa_op->result_def].var < op_array->num_args) {
		return 1;
	}
	return 0;
}