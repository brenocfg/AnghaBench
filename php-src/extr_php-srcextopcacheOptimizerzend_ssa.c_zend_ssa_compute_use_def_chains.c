#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_34__ {int var; int scc; int definition; int use_chain; int /*<<< orphan*/  alias; TYPE_11__* phi_use_chain; TYPE_11__* sym_use_chain; TYPE_11__* definition_phi; } ;
typedef  TYPE_9__ zend_ssa_var ;
struct TYPE_21__ {size_t min_ssa_var; size_t max_ssa_var; } ;
typedef  TYPE_10__ zend_ssa_range_constraint ;
struct TYPE_31__ {TYPE_10__ range; } ;
struct TYPE_22__ {int block; size_t ssa_var; int var; scalar_t__ pi; size_t* sources; struct TYPE_22__* next; struct TYPE_22__** use_chains; struct TYPE_22__* sym_use_chain; TYPE_6__ constraint; scalar_t__ has_range_constraint; } ;
typedef  TYPE_11__ zend_ssa_phi ;
struct TYPE_23__ {size_t op1_use; int op1_use_chain; size_t op2_use; int op2_use_chain; size_t result_use; int res_use_chain; size_t op1_def; size_t op2_def; size_t result_def; } ;
typedef  TYPE_12__ zend_ssa_op ;
struct TYPE_33__ {int blocks_count; int flags; TYPE_7__* blocks; } ;
struct TYPE_24__ {int vars_count; TYPE_8__ cfg; TYPE_5__* blocks; TYPE_12__* ops; TYPE_9__* vars; } ;
typedef  TYPE_13__ zend_ssa ;
struct TYPE_25__ {int last_var; int last; int /*<<< orphan*/ * vars; TYPE_4__* opcodes; } ;
typedef  TYPE_14__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_arena ;
struct TYPE_32__ {int predecessors_count; } ;
struct TYPE_30__ {TYPE_11__* phis; } ;
struct TYPE_28__ {int /*<<< orphan*/  var; } ;
struct TYPE_27__ {int /*<<< orphan*/  var; } ;
struct TYPE_26__ {int /*<<< orphan*/  var; } ;
struct TYPE_29__ {TYPE_3__ result; TYPE_2__ op2; TYPE_1__ op1; } ;

/* Variables and functions */
 void* EX_VAR_TO_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTTP_RESPONSE_HEADER_ALIAS ; 
 int SUCCESS ; 
 int /*<<< orphan*/  SYMTABLE_ALIAS ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_FUNC_INDIRECT_VAR_ACCESS ; 
 TYPE_9__* zend_arena_calloc (int /*<<< orphan*/ **,int,int) ; 
 TYPE_11__* zend_ssa_next_use_phi (TYPE_13__*,size_t,TYPE_11__*) ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ ,char*) ; 

int zend_ssa_compute_use_def_chains(zend_arena **arena, const zend_op_array *op_array, zend_ssa *ssa) /* {{{ */
{
	zend_ssa_var *ssa_vars;
	int i;

	if (!ssa->vars) {
		ssa->vars = zend_arena_calloc(arena, ssa->vars_count, sizeof(zend_ssa_var));
	}
	ssa_vars = ssa->vars;

	for (i = 0; i < op_array->last_var; i++) {
		ssa_vars[i].var = i;
		ssa_vars[i].scc = -1;
		ssa_vars[i].definition = -1;
		ssa_vars[i].use_chain = -1;
	}
	for (i = op_array->last_var; i < ssa->vars_count; i++) {
		ssa_vars[i].var = -1;
		ssa_vars[i].scc = -1;
		ssa_vars[i].definition = -1;
		ssa_vars[i].use_chain = -1;
	}

	for (i = op_array->last - 1; i >= 0; i--) {
		zend_ssa_op *op = ssa->ops + i;

		if (op->op1_use >= 0) {
			op->op1_use_chain = ssa_vars[op->op1_use].use_chain;
			ssa_vars[op->op1_use].use_chain = i;
		}
		if (op->op2_use >= 0 && op->op2_use != op->op1_use) {
			op->op2_use_chain = ssa_vars[op->op2_use].use_chain;
			ssa_vars[op->op2_use].use_chain = i;
		}
		if (op->result_use >= 0 && op->result_use != op->op1_use && op->result_use != op->op2_use) {
			op->res_use_chain = ssa_vars[op->result_use].use_chain;
			ssa_vars[op->result_use].use_chain = i;
		}
		if (op->op1_def >= 0) {
			ssa_vars[op->op1_def].var = EX_VAR_TO_NUM(op_array->opcodes[i].op1.var);
			ssa_vars[op->op1_def].definition = i;
		}
		if (op->op2_def >= 0) {
			ssa_vars[op->op2_def].var = EX_VAR_TO_NUM(op_array->opcodes[i].op2.var);
			ssa_vars[op->op2_def].definition = i;
		}
		if (op->result_def >= 0) {
			ssa_vars[op->result_def].var = EX_VAR_TO_NUM(op_array->opcodes[i].result.var);
			ssa_vars[op->result_def].definition = i;
		}
	}

	for (i = 0; i < ssa->cfg.blocks_count; i++) {
		zend_ssa_phi *phi = ssa->blocks[i].phis;
		while (phi) {
			phi->block = i;
			ssa_vars[phi->ssa_var].var = phi->var;
			ssa_vars[phi->ssa_var].definition_phi = phi;
			if (phi->pi >= 0) {
				zend_ssa_phi *p;

				ZEND_ASSERT(phi->sources[0] >= 0);
				p = ssa_vars[phi->sources[0]].phi_use_chain;
				while (p && p != phi) {
					p = zend_ssa_next_use_phi(ssa, phi->sources[0], p);
				}
				if (!p) {
					phi->use_chains[0] = ssa_vars[phi->sources[0]].phi_use_chain;
					ssa_vars[phi->sources[0]].phi_use_chain = phi;
				}
				if (phi->has_range_constraint) {
					/* min and max variables can't be used together */
					zend_ssa_range_constraint *constraint = &phi->constraint.range;
					if (constraint->min_ssa_var >= 0) {
						phi->sym_use_chain = ssa_vars[constraint->min_ssa_var].sym_use_chain;
						ssa_vars[constraint->min_ssa_var].sym_use_chain = phi;
					} else if (constraint->max_ssa_var >= 0) {
						phi->sym_use_chain = ssa_vars[constraint->max_ssa_var].sym_use_chain;
						ssa_vars[constraint->max_ssa_var].sym_use_chain = phi;
					}
				}
			} else {
				int j;

				for (j = 0; j < ssa->cfg.blocks[i].predecessors_count; j++) {
					zend_ssa_phi *p;

					ZEND_ASSERT(phi->sources[j] >= 0);
					p = ssa_vars[phi->sources[j]].phi_use_chain;
					while (p && p != phi) {
						p = zend_ssa_next_use_phi(ssa, phi->sources[j], p);
					}
					if (!p) {
						phi->use_chains[j] = ssa_vars[phi->sources[j]].phi_use_chain;
						ssa_vars[phi->sources[j]].phi_use_chain = phi;
					}
				}
			}
			phi = phi->next;
		}
	}

	/* Mark indirectly accessed variables */
	for (i = 0; i < op_array->last_var; i++) {
		if ((ssa->cfg.flags & ZEND_FUNC_INDIRECT_VAR_ACCESS)) {
			ssa_vars[i].alias = SYMTABLE_ALIAS;
		} else if (zend_string_equals_literal(op_array->vars[i], "http_response_header")) {
			ssa_vars[i].alias = HTTP_RESPONSE_HEADER_ALIAS;
		}
	}
	for (i = op_array->last_var; i < ssa->vars_count; i++) {
		if (ssa_vars[i].var < op_array->last_var) {
			ssa_vars[i].alias = ssa_vars[ssa_vars[i].var].alias;
		}
	}

	return SUCCESS;
}