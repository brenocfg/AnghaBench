#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ len; } ;
typedef  TYPE_2__ zend_worklist_stack ;
struct TYPE_12__ {struct TYPE_12__* sym_use_chain; int /*<<< orphan*/  ssa_var; } ;
typedef  TYPE_3__ zend_ssa_phi ;
struct TYPE_13__ {int /*<<< orphan*/  sccs; TYPE_1__* vars; } ;
typedef  TYPE_4__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_10__ {int /*<<< orphan*/  scc; TYPE_3__* sym_use_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SCC_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOR_EACH_VAR_USAGE (int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int zend_worklist_stack_peek (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_worklist_stack_pop (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_worklist_stack_push (TYPE_2__*,int) ; 

__attribute__((used)) static void zend_ssa_check_scc_var(const zend_op_array *op_array, zend_ssa *ssa, int var, int *index, int *dfs, int *root, zend_worklist_stack *stack) /* {{{ */
{
#ifdef SYM_RANGE
	zend_ssa_phi *p;
#endif

	dfs[var] = *index;
	(*index)++;
	root[var] = var;

	FOR_EACH_VAR_USAGE(var, CHECK_SCC_VAR);

#ifdef SYM_RANGE
	/* Process symbolic control-flow constraints */
	p = ssa->vars[var].sym_use_chain;
	while (p) {
		CHECK_SCC_VAR(p->ssa_var);
		p = p->sym_use_chain;
	}
#endif

	if (root[var] == var) {
		ssa->vars[var].scc = ssa->sccs;
		while (stack->len > 0) {
			int var2 = zend_worklist_stack_peek(stack);
			if (dfs[var2] <= dfs[var]) {
				break;
			}
			zend_worklist_stack_pop(stack);
			ssa->vars[var2].scc = ssa->sccs;
		}
		ssa->sccs++;
	} else {
		zend_worklist_stack_push(stack, var);
	}
}