#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* ops; TYPE_1__* vars; } ;
typedef  TYPE_2__ zend_ssa ;
struct TYPE_7__ {int result_use; int res_use_chain; int op1_use; int op1_use_chain; int op2_use; int op2_use_chain; } ;
struct TYPE_5__ {int use_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 void* zend_ssa_next_use (TYPE_4__*,int,int) ; 

int zend_ssa_unlink_use_chain(zend_ssa *ssa, int op, int var) /* {{{ */
{
	if (ssa->vars[var].use_chain == op) {
		ssa->vars[var].use_chain = zend_ssa_next_use(ssa->ops, var, op);
		return 1;
	} else {
		int use = ssa->vars[var].use_chain;

		while (use >= 0) {
			if (ssa->ops[use].result_use == var) {
				if (ssa->ops[use].res_use_chain == op) {
					ssa->ops[use].res_use_chain = zend_ssa_next_use(ssa->ops, var, op);
					return 1;
				} else {
					use = ssa->ops[use].res_use_chain;
				}
			} else if (ssa->ops[use].op1_use == var) {
				if (ssa->ops[use].op1_use_chain == op) {
					ssa->ops[use].op1_use_chain = zend_ssa_next_use(ssa->ops, var, op);
					return 1;
				} else {
					use = ssa->ops[use].op1_use_chain;
				}
			} else if (ssa->ops[use].op2_use == var) {
				if (ssa->ops[use].op2_use_chain == op) {
					ssa->ops[use].op2_use_chain = zend_ssa_next_use(ssa->ops, var, op);
					return 1;
				} else {
					use = ssa->ops[use].op2_use_chain;
				}
			} else {
				break;
			}
		}
		/* something wrong */
		ZEND_ASSERT(0);
		return 0;
	}
}