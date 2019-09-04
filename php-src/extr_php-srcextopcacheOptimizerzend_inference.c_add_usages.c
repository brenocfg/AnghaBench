#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ ssa_var; } ;
typedef  TYPE_3__ zend_ssa_phi ;
struct TYPE_16__ {scalar_t__ result_def; scalar_t__ op1_def; scalar_t__ op2_def; } ;
typedef  TYPE_4__ zend_ssa_op ;
struct TYPE_17__ {TYPE_4__* ops; TYPE_1__* vars; } ;
typedef  TYPE_5__ zend_ssa ;
struct TYPE_18__ {TYPE_2__* opcodes; } ;
typedef  TYPE_6__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_bitset ;
struct TYPE_14__ {scalar_t__ opcode; } ;
struct TYPE_13__ {int use_chain; TYPE_3__* phi_use_chain; } ;

/* Variables and functions */
 scalar_t__ ZEND_OP_DATA ; 
 int /*<<< orphan*/  zend_bitset_incl (int /*<<< orphan*/ ,scalar_t__) ; 
 int zend_ssa_next_use (TYPE_4__*,int,int) ; 
 TYPE_3__* zend_ssa_next_use_phi (TYPE_5__*,int,TYPE_3__*) ; 

__attribute__((used)) static void add_usages(const zend_op_array *op_array, zend_ssa *ssa, zend_bitset worklist, int var)
{
	if (ssa->vars[var].phi_use_chain) {
		zend_ssa_phi *p = ssa->vars[var].phi_use_chain;
		do {
			zend_bitset_incl(worklist, p->ssa_var);
			p = zend_ssa_next_use_phi(ssa, var, p);
		} while (p);
	}
	if (ssa->vars[var].use_chain >= 0) {
		int use = ssa->vars[var].use_chain;
		zend_ssa_op *op;

		do {
			op = ssa->ops + use;
			if (op->result_def >= 0) {
				zend_bitset_incl(worklist, op->result_def);
			}
			if (op->op1_def >= 0) {
				zend_bitset_incl(worklist, op->op1_def);
			}
			if (op->op2_def >= 0) {
				zend_bitset_incl(worklist, op->op2_def);
			}
			if (op_array->opcodes[use].opcode == ZEND_OP_DATA) {
				op--;
				if (op->result_def >= 0) {
					zend_bitset_incl(worklist, op->result_def);
				}
				if (op->op1_def >= 0) {
					zend_bitset_incl(worklist, op->op1_def);
				}
				if (op->op2_def >= 0) {
					zend_bitset_incl(worklist, op->op2_def);
				}
			}
			use = zend_ssa_next_use(ssa->ops, var, use);
		} while (use >= 0);
	}
}