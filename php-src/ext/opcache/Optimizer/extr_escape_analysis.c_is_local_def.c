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
struct TYPE_9__ {int result_def; int op1_def; } ;
typedef  TYPE_1__ zend_ssa_op ;
struct TYPE_10__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_script ;
struct TYPE_11__ {TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_12__ {int opcode; int /*<<< orphan*/  op1; int /*<<< orphan*/  op1_type; } ;
typedef  TYPE_4__ zend_op ;
struct TYPE_13__ {int ce_flags; int /*<<< orphan*/  __set; int /*<<< orphan*/  __get; int /*<<< orphan*/  destructor; int /*<<< orphan*/  constructor; int /*<<< orphan*/  create_object; } ;
typedef  TYPE_5__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_CONSTANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_CONST ; 
 int ZEND_ACC_INHERITED ; 
#define  ZEND_ADD_ARRAY_ELEMENT 141 
#define  ZEND_ASSIGN 140 
#define  ZEND_ASSIGN_DIM 139 
#define  ZEND_ASSIGN_DIM_OP 138 
#define  ZEND_ASSIGN_OBJ 137 
#define  ZEND_ASSIGN_OBJ_OP 136 
#define  ZEND_ASSIGN_OBJ_REF 135 
#define  ZEND_INIT_ARRAY 134 
#define  ZEND_NEW 133 
#define  ZEND_POST_DEC_OBJ 132 
#define  ZEND_POST_INC_OBJ 131 
#define  ZEND_PRE_DEC_OBJ 130 
#define  ZEND_PRE_INC_OBJ 129 
#define  ZEND_QM_ASSIGN 128 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ ) ; 
 TYPE_5__* get_class_entry (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_local_def(zend_op_array *op_array, zend_ssa *ssa, int def, int var, const zend_script *script) /* {{{ */
{
	zend_ssa_op *op = ssa->ops + def;
	zend_op *opline = op_array->opcodes + def;

	if (op->result_def == var) {
		switch (opline->opcode) {
			case ZEND_INIT_ARRAY:
			case ZEND_ADD_ARRAY_ELEMENT:
			case ZEND_QM_ASSIGN:
			case ZEND_ASSIGN:
				return 1;
			case ZEND_NEW:
				/* objects with destructors should escape */
				if (opline->op1_type == IS_CONST) {
					zend_class_entry *ce = get_class_entry(script, Z_STR_P(CRT_CONSTANT(opline->op1)+1));
					if (ce && !ce->create_object && !ce->constructor &&
					    !ce->destructor && !ce->__get && !ce->__set &&
					    !(ce->ce_flags & ZEND_ACC_INHERITED)) {
						return 1;
					}
				}
				break;
		}
	} else if (op->op1_def == var) {
		switch (opline->opcode) {
			case ZEND_ASSIGN:
			case ZEND_ASSIGN_DIM:
			case ZEND_ASSIGN_OBJ:
			case ZEND_ASSIGN_OBJ_REF:
			case ZEND_ASSIGN_DIM_OP:
			case ZEND_ASSIGN_OBJ_OP:
			case ZEND_PRE_INC_OBJ:
			case ZEND_PRE_DEC_OBJ:
			case ZEND_POST_INC_OBJ:
			case ZEND_POST_DEC_OBJ:
				return 1;
		}
	}

	return 0;
}