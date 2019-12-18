#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_9__ {int type; int type2; } ;
struct TYPE_8__ {TYPE_2__* current_bb_head; TYPE_2__* current_bb; } ;
typedef  TYPE_1__ RAnalState ;
typedef  TYPE_2__ RAnalBlock ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int R_ANAL_BB_TYPE_TAIL ; 
 int R_ANAL_EX_CODE_OP ; 
 int /*<<< orphan*/  handle_bb_cf_recursive_descent (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  r_anal_ex_update_bb_cfg_head_tail (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int java_recursive_descent(RAnal *anal, RAnalState *state, ut64 addr) {
	r_return_val_if_fail (anal && state && state->current_bb && state->current_bb_head, 0);

	RAnalBlock *bb = state->current_bb;
	RAnalBlock *head = state->current_bb_head;

	if (head && bb->type & R_ANAL_BB_TYPE_TAIL) {
		r_anal_ex_update_bb_cfg_head_tail (head, head, bb);
	}

	// basic filter for handling the different type of operations
	// depending on flags some may be called more than once
	// if (bb->type2 & R_ANAL_EX_ILL_OP)   handle_bb_ill_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_COND_OP)  handle_bb_cond_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_UNK_OP)   handle_bb_unknown_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_NULL_OP)  handle_bb_null_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_NOP_OP)   handle_bb_nop_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_REP_OP)   handle_bb_rep_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_STORE_OP) handle_bb_store_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_LOAD_OP)  handle_bb_load_op (anal, state
	// if (bb->type2 & R_ANAL_EX_REG_OP)   handle_bb_reg_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_OBJ_OP)   handle_bb_obj_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_STACK_OP) handle_bb_stack_op (anal, state);
	// if (bb->type2 & R_ANAL_EX_BIN_OP)   handle_bb_bin_op (anal, state);
	if (bb->type2 & R_ANAL_EX_CODE_OP) {
		handle_bb_cf_recursive_descent (anal, state);
	}
	// if (bb->type2 & R_ANAL_EX_DATA_OP)  handle_bb_data_op (anal, state);
	return 0;
}