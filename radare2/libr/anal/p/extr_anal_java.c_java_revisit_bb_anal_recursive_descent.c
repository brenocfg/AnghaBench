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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_8__ {int type; } ;
struct TYPE_7__ {int done; TYPE_2__* current_bb; TYPE_2__* current_bb_head; } ;
typedef  TYPE_1__ RAnalState ;
typedef  TYPE_2__ RAnalBlock ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int R_ANAL_BB_TYPE_TAIL ; 
 int R_ANAL_RET_END ; 
 int /*<<< orphan*/  R_ANAL_RET_ERROR ; 
 int /*<<< orphan*/  r_anal_ex_update_bb_cfg_head_tail (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int java_revisit_bb_anal_recursive_descent(RAnal *anal, RAnalState *state, ut64 addr) {
	r_return_val_if_fail (anal && state, R_ANAL_RET_ERROR);
	RAnalBlock *head = state->current_bb_head;
	RAnalBlock *bb = state->current_bb;
	r_return_val_if_fail (bb && head, R_ANAL_RET_ERROR);
	if (bb->type & R_ANAL_BB_TYPE_TAIL) {
		r_anal_ex_update_bb_cfg_head_tail (head, head, bb);
		// XXX should i do this instead -> r_anal_ex_perform_post_anal_bb_cb (anal, state, addr+offset);
		state->done = 1;
	}
	return R_ANAL_RET_END;
}