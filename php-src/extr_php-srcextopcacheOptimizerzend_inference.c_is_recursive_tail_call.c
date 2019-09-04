#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_6__* opcodes; } ;
typedef  TYPE_5__ zend_op_array ;
struct TYPE_18__ {scalar_t__ opcode; } ;
typedef  TYPE_6__ zend_op ;
struct TYPE_15__ {TYPE_2__* ops; TYPE_1__* vars; } ;
struct TYPE_19__ {TYPE_8__** call_map; TYPE_3__ ssa; } ;
typedef  TYPE_7__ zend_func_info ;
struct TYPE_20__ {TYPE_4__* callee_func; } ;
typedef  TYPE_8__ zend_call_info ;
struct TYPE_16__ {TYPE_5__ const op_array; } ;
struct TYPE_14__ {size_t op1_use; } ;
struct TYPE_13__ {scalar_t__ definition; } ;

/* Variables and functions */
 scalar_t__ ZEND_DO_UCALL ; 
 TYPE_7__* ZEND_FUNC_INFO (TYPE_5__ const*) ; 

__attribute__((used)) static int is_recursive_tail_call(const zend_op_array *op_array,
                                  zend_op             *opline)
{
	zend_func_info *info = ZEND_FUNC_INFO(op_array);

	if (info->ssa.ops && info->ssa.vars && info->call_map &&
	    info->ssa.ops[opline - op_array->opcodes].op1_use >= 0 &&
	    info->ssa.vars[info->ssa.ops[opline - op_array->opcodes].op1_use].definition >= 0) {

		zend_op *op = op_array->opcodes + info->ssa.vars[info->ssa.ops[opline - op_array->opcodes].op1_use].definition;

		if (op->opcode == ZEND_DO_UCALL) {
			zend_call_info *call_info = info->call_map[op - op_array->opcodes];
			if (call_info && op_array == &call_info->callee_func->op_array) {
				return 1;
			}
		}
	}
	return 0;
}