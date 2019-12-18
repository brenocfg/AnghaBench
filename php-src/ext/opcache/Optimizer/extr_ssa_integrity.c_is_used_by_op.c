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
struct TYPE_4__ {int op1_use; int op2_use; int result_use; } ;
typedef  TYPE_1__ zend_ssa_op ;
struct TYPE_5__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ zend_ssa ;
typedef  int zend_bool ;

/* Variables and functions */

__attribute__((used)) static inline zend_bool is_used_by_op(zend_ssa *ssa, int op, int check) {
	zend_ssa_op *ssa_op = &ssa->ops[op];
	return (ssa_op->op1_use == check)
		|| (ssa_op->op2_use == check)
		|| (ssa_op->result_use == check);
}