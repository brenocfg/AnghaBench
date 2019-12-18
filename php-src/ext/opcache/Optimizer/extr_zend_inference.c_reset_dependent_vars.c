#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ type; } ;
typedef  TYPE_2__ zend_ssa_var_info ;
struct TYPE_16__ {int use_chain; TYPE_4__* sym_use_chain; TYPE_4__* phi_use_chain; } ;
typedef  TYPE_3__ zend_ssa_var ;
struct TYPE_17__ {size_t ssa_var; struct TYPE_17__* sym_use_chain; } ;
typedef  TYPE_4__ zend_ssa_phi ;
struct TYPE_18__ {size_t op1_def; size_t op2_def; size_t result_def; } ;
typedef  TYPE_5__ zend_ssa_op ;
struct TYPE_19__ {TYPE_3__* vars; TYPE_2__* var_info; TYPE_5__* ops; } ;
typedef  TYPE_6__ zend_ssa ;
struct TYPE_20__ {TYPE_1__* opcodes; } ;
typedef  TYPE_7__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_bitset ;
struct TYPE_14__ {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ ZEND_OP_DATA ; 
 int /*<<< orphan*/  zend_bitset_incl (int /*<<< orphan*/ ,size_t) ; 
 int zend_ssa_next_use (TYPE_5__*,int,int) ; 
 TYPE_4__* zend_ssa_next_use_phi (TYPE_6__*,int,TYPE_4__*) ; 

__attribute__((used)) static void reset_dependent_vars(const zend_op_array *op_array, zend_ssa *ssa, zend_bitset worklist, int var)
{
	zend_ssa_op *ssa_ops = ssa->ops;
	zend_ssa_var *ssa_vars = ssa->vars;
	zend_ssa_var_info *ssa_var_info = ssa->var_info;
	zend_ssa_phi *p;
	int use;

	p = ssa_vars[var].phi_use_chain;
	while (p) {
		if (ssa_var_info[p->ssa_var].type) {
			ssa_var_info[p->ssa_var].type = 0;
			zend_bitset_incl(worklist, p->ssa_var);
			reset_dependent_vars(op_array, ssa, worklist, p->ssa_var);
		}
		p = zend_ssa_next_use_phi(ssa, var, p);
	}
	use = ssa_vars[var].use_chain;
	while (use >= 0) {
		if (ssa_ops[use].op1_def >= 0 && ssa_var_info[ssa_ops[use].op1_def].type) {
			ssa_var_info[ssa_ops[use].op1_def].type = 0;
			zend_bitset_incl(worklist, ssa_ops[use].op1_def);
			reset_dependent_vars(op_array, ssa, worklist, ssa_ops[use].op1_def);
		}
		if (ssa_ops[use].op2_def >= 0 && ssa_var_info[ssa_ops[use].op2_def].type) {
			ssa_var_info[ssa_ops[use].op2_def].type = 0;
			zend_bitset_incl(worklist, ssa_ops[use].op2_def);
			reset_dependent_vars(op_array, ssa, worklist, ssa_ops[use].op2_def);
		}
		if (ssa_ops[use].result_def >= 0 && ssa_var_info[ssa_ops[use].result_def].type) {
			ssa_var_info[ssa_ops[use].result_def].type = 0;
			zend_bitset_incl(worklist, ssa_ops[use].result_def);
			reset_dependent_vars(op_array, ssa, worklist, ssa_ops[use].result_def);
		}
		if (op_array->opcodes[use+1].opcode == ZEND_OP_DATA) {
			if (ssa_ops[use+1].op1_def >= 0 && ssa_var_info[ssa_ops[use+1].op1_def].type) {
				ssa_var_info[ssa_ops[use+1].op1_def].type = 0;
				zend_bitset_incl(worklist, ssa_ops[use+1].op1_def);
				reset_dependent_vars(op_array, ssa, worklist, ssa_ops[use+1].op1_def);
			}
			if (ssa_ops[use+1].op2_def >= 0 && ssa_var_info[ssa_ops[use+1].op2_def].type) {
				ssa_var_info[ssa_ops[use+1].op2_def].type = 0;
				zend_bitset_incl(worklist, ssa_ops[use+1].op2_def);
				reset_dependent_vars(op_array, ssa, worklist, ssa_ops[use+1].op2_def);
			}
			if (ssa_ops[use+1].result_def >= 0 && ssa_var_info[ssa_ops[use+1].result_def].type) {
				ssa_var_info[ssa_ops[use+1].result_def].type = 0;
				zend_bitset_incl(worklist, ssa_ops[use+1].result_def);
				reset_dependent_vars(op_array, ssa, worklist, ssa_ops[use+1].result_def);
			}
		}
		use = zend_ssa_next_use(ssa_ops, var, use);
	}
#ifdef SYM_RANGE
	/* Process symbolic control-flow constraints */
	p = ssa->vars[var].sym_use_chain;
	while (p) {
		ssa_var_info[p->ssa_var].type = 0;
		zend_bitset_incl(worklist, p->ssa_var);
		reset_dependent_vars(op_array, ssa, worklist, p->ssa_var);
		p = p->sym_use_chain;
	}
#endif
}