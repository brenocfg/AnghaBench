#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_send_arg_info ;
typedef  int /*<<< orphan*/  zend_script ;
struct TYPE_19__ {int last; TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_17__ {size_t num; } ;
struct TYPE_20__ {int opcode; int extended_value; TYPE_1__ op2; } ;
typedef  TYPE_4__ zend_op ;
struct TYPE_21__ {int /*<<< orphan*/  op_array; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ zend_function ;
struct TYPE_22__ {int /*<<< orphan*/  flags; TYPE_7__* caller_info; TYPE_7__* callee_info; } ;
typedef  TYPE_6__ zend_func_info ;
struct TYPE_23__ {int num_args; TYPE_2__* arg_info; TYPE_4__* caller_call_opline; struct TYPE_23__* next_caller; struct TYPE_23__* next_callee; TYPE_5__* callee_func; TYPE_4__* caller_init_opline; TYPE_3__* caller_op_array; } ;
typedef  TYPE_7__ zend_call_info ;
typedef  int /*<<< orphan*/  zend_arena ;
typedef  size_t uint32_t ;
struct TYPE_18__ {TYPE_4__* opline; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCA_FLAG (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 size_t ZEND_CALL_TREE ; 
#define  ZEND_DO_FCALL 150 
#define  ZEND_DO_FCALL_BY_NAME 149 
#define  ZEND_DO_ICALL 148 
#define  ZEND_DO_UCALL 147 
 int /*<<< orphan*/  ZEND_FUNC_HAS_CALLS ; 
 TYPE_6__* ZEND_FUNC_INFO (int /*<<< orphan*/ *) ; 
#define  ZEND_INIT_DYNAMIC_CALL 146 
#define  ZEND_INIT_FCALL 145 
#define  ZEND_INIT_FCALL_BY_NAME 144 
#define  ZEND_INIT_METHOD_CALL 143 
#define  ZEND_INIT_NS_FCALL_BY_NAME 142 
#define  ZEND_INIT_STATIC_METHOD_CALL 141 
#define  ZEND_INIT_USER_CALL 140 
 int /*<<< orphan*/  ZEND_INTERNAL_FUNCTION ; 
#define  ZEND_NEW 139 
#define  ZEND_SEND_ARRAY 138 
#define  ZEND_SEND_FUNC_ARG 137 
#define  ZEND_SEND_REF 136 
#define  ZEND_SEND_UNPACK 135 
#define  ZEND_SEND_USER 134 
#define  ZEND_SEND_VAL 133 
#define  ZEND_SEND_VAL_EX 132 
#define  ZEND_SEND_VAR 131 
#define  ZEND_SEND_VAR_EX 130 
#define  ZEND_SEND_VAR_NO_REF 129 
#define  ZEND_SEND_VAR_NO_REF_EX 128 
 TYPE_7__** do_alloca (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_alloca (TYPE_7__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_heap ; 
 TYPE_7__* zend_arena_calloc (int /*<<< orphan*/ **,int,int) ; 
 TYPE_5__* zend_optimizer_get_called_func (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*) ; 

int zend_analyze_calls(zend_arena **arena, zend_script *script, uint32_t build_flags, zend_op_array *op_array, zend_func_info *func_info)
{
	zend_op *opline = op_array->opcodes;
	zend_op *end = opline + op_array->last;
	zend_function *func;
	zend_call_info *call_info;
	int call = 0;
	zend_call_info **call_stack;
	ALLOCA_FLAG(use_heap);

	call_stack = do_alloca((op_array->last / 2) * sizeof(zend_call_info*), use_heap);
	call_info = NULL;
	while (opline != end) {
		switch (opline->opcode) {
			case ZEND_INIT_FCALL:
			case ZEND_INIT_METHOD_CALL:
			case ZEND_INIT_STATIC_METHOD_CALL:
				call_stack[call] = call_info;
				func = zend_optimizer_get_called_func(
					script, op_array, opline);
				if (func) {
					call_info = zend_arena_calloc(arena, 1, sizeof(zend_call_info) + (sizeof(zend_send_arg_info) * ((int)opline->extended_value - 1)));
					call_info->caller_op_array = op_array;
					call_info->caller_init_opline = opline;
					call_info->caller_call_opline = NULL;
					call_info->callee_func = func;
					call_info->num_args = opline->extended_value;
					call_info->next_callee = func_info->callee_info;
					func_info->callee_info = call_info;

					if (build_flags & ZEND_CALL_TREE) {
						call_info->next_caller = NULL;
					} else if (func->type == ZEND_INTERNAL_FUNCTION) {
						call_info->next_caller = NULL;
					} else {
						zend_func_info *callee_func_info = ZEND_FUNC_INFO(&func->op_array);
						if (callee_func_info) {
							call_info->next_caller = callee_func_info->caller_info;
							callee_func_info->caller_info = call_info;
						} else {
							call_info->next_caller = NULL;
						}
					}
				} else {
					call_info = NULL;
				}
				call++;
				break;
			case ZEND_INIT_FCALL_BY_NAME:
			case ZEND_INIT_NS_FCALL_BY_NAME:
			case ZEND_INIT_DYNAMIC_CALL:
			case ZEND_NEW:
			case ZEND_INIT_USER_CALL:
				call_stack[call] = call_info;
				call_info = NULL;
				call++;
				break;
			case ZEND_DO_FCALL:
			case ZEND_DO_ICALL:
			case ZEND_DO_UCALL:
			case ZEND_DO_FCALL_BY_NAME:
				func_info->flags |= ZEND_FUNC_HAS_CALLS;
				if (call_info) {
					call_info->caller_call_opline = opline;
				}
				call--;
				call_info = call_stack[call];
				break;
			case ZEND_SEND_VAL:
			case ZEND_SEND_VAR:
			case ZEND_SEND_VAL_EX:
			case ZEND_SEND_VAR_EX:
			case ZEND_SEND_FUNC_ARG:
			case ZEND_SEND_REF:
			case ZEND_SEND_VAR_NO_REF:
			case ZEND_SEND_VAR_NO_REF_EX:
			case ZEND_SEND_USER:
				if (call_info) {
					uint32_t num = opline->op2.num;

					if (num > 0) {
						num--;
					}
					call_info->arg_info[num].opline = opline;
				}
				break;
			case ZEND_SEND_ARRAY:
			case ZEND_SEND_UNPACK:
				/* TODO: set info about var_arg call ??? */
				if (call_info) {
					call_info->num_args = -1;
				}
				break;
		}
		opline++;
	}
	free_alloca(call_stack, use_heap);
	return SUCCESS;
}