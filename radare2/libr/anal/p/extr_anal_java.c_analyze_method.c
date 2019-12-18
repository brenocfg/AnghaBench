#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  bbs; } ;
struct TYPE_6__ {int anal_ret_val; TYPE_2__* current_fcn; } ;
typedef  TYPE_1__ RAnalState ;
typedef  TYPE_2__ RAnalFunction ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  java_new_method (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_bb_list_new () ; 
 int /*<<< orphan*/  r_anal_ex_perform_analysis (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int analyze_method(RAnal *anal, RAnalFunction *fcn, RAnalState *state) {
	// deallocate niceties
	r_list_free (fcn->bbs);
	fcn->bbs = r_anal_bb_list_new ();
	java_new_method (fcn->addr);
	state->current_fcn = fcn;
	// Not a resource leak.  Basic blocks should be stored in the state->fcn
	// TODO: ? RList *bbs =
	r_anal_ex_perform_analysis (anal, state, fcn->addr);
	return state->anal_ret_val;
}