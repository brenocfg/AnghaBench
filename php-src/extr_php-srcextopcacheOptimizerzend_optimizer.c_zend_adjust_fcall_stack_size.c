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
struct TYPE_11__ {TYPE_1__* script; } ;
typedef  TYPE_3__ zend_optimizer_ctx ;
struct TYPE_12__ {int last; TYPE_5__* opcodes; } ;
typedef  TYPE_4__ zend_op_array ;
struct TYPE_10__ {int /*<<< orphan*/  num; } ;
struct TYPE_13__ {scalar_t__ opcode; int /*<<< orphan*/  extended_value; TYPE_2__ op1; int /*<<< orphan*/  op2; } ;
typedef  TYPE_5__ zend_op ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_9__ {int /*<<< orphan*/  function_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_CONSTANT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_INIT_FCALL ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_vm_calc_used_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_adjust_fcall_stack_size(zend_op_array *op_array, zend_optimizer_ctx *ctx)
{
	zend_function *func;
	zend_op *opline, *end;

	opline = op_array->opcodes;
	end = opline + op_array->last;
	while (opline < end) {
		if (opline->opcode == ZEND_INIT_FCALL) {
			func = zend_hash_find_ptr(
				&ctx->script->function_table,
				Z_STR_P(RT_CONSTANT(opline, opline->op2)));
			if (func) {
				opline->op1.num = zend_vm_calc_used_stack(opline->extended_value, func);
			}
		}
		opline++;
	}
}