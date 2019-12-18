#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_15__ {scalar_t__ addr; scalar_t__ jump; scalar_t__ fail; int op_pos_size; scalar_t__* op_pos; } ;
struct TYPE_14__ {scalar_t__ type; scalar_t__ jump; } ;
struct TYPE_13__ {scalar_t__ followDepth; int /*<<< orphan*/  visited; int /*<<< orphan*/  path; TYPE_4__* cur; int /*<<< orphan*/  core; scalar_t__ followCalls; TYPE_1__* toBB; } ;
struct TYPE_12__ {scalar_t__ addr; } ;
typedef  TYPE_2__ RCoreAnalPaths ;
typedef  TYPE_3__ RAnalOp ;
typedef  TYPE_4__ RAnalBlock ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 scalar_t__ R_ANAL_OP_TYPE_CALL ; 
 int /*<<< orphan*/  analPathFollow (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dict_del (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dict_set (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printAnalPaths (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_anal_op_free (TYPE_3__*) ; 
 scalar_t__ r_cons_is_breaked () ; 
 TYPE_3__* r_core_anal_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* r_list_pop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void analPaths(RCoreAnalPaths *p, PJ *pj) {
	RAnalBlock *cur = p->cur;
	if (!cur) {
		// eprintf ("eof\n");
		return;
	}
	/* handle ^C */
	if (r_cons_is_breaked ()) {
		return;
	}
	dict_set (&p->visited, cur->addr, 1, NULL);
	r_list_append (p->path, cur);
	if (p->followDepth && --p->followDepth == 0) {
		return;
	}
	if (p->toBB && cur->addr == p->toBB->addr) {
		if (!printAnalPaths (p, pj)) {
			return;
		}
	} else {
		RAnalBlock *c = cur;
		ut64 j = cur->jump;
		ut64 f = cur->fail;
		analPathFollow (p, j, pj);
		cur = c;
		analPathFollow (p, f, pj);
		if (p->followCalls) {
			int i;
			for (i = 0; i < cur->op_pos_size; i++) {
				ut64 addr = cur->addr + cur->op_pos[i];
				RAnalOp *op = r_core_anal_op (p->core, addr, R_ANAL_OP_MASK_BASIC);
				if (op && op->type == R_ANAL_OP_TYPE_CALL) {
					analPathFollow (p, op->jump, pj);
				}
				cur = c;
				r_anal_op_free (op);
			}
		}
	}
	p->cur = r_list_pop (p->path);
	dict_del (&p->visited, cur->addr);
	if (p->followDepth) {
		p->followDepth++;
	}
}