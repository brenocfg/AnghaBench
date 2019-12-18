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
struct TYPE_10__ {TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_8__ {scalar_t__ var; } ;
struct TYPE_9__ {scalar_t__ var; } ;
struct TYPE_11__ {scalar_t__ opcode; scalar_t__ extended_value; int result_type; TYPE_1__ result; TYPE_2__ op1; } ;
typedef  TYPE_4__ zend_op ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int IS_TMP_VAR ; 
 int IS_VAR ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_FE_FREE ; 
 scalar_t__ ZEND_FREE ; 
 scalar_t__ ZEND_FREE_SWITCH ; 

zend_op *zend_optimizer_get_loop_var_def(const zend_op_array *op_array, zend_op *free_opline) {
	uint32_t var = free_opline->op1.var;
	ZEND_ASSERT(free_opline->opcode == ZEND_FE_FREE ||
		(free_opline->opcode == ZEND_FREE && free_opline->extended_value == ZEND_FREE_SWITCH));

	while (--free_opline >= op_array->opcodes) {
		if ((free_opline->result_type & (IS_TMP_VAR|IS_VAR)) && free_opline->result.var == var) {
			return free_opline;
		}
	}
	return NULL;
}