#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_uchar ;
struct TYPE_26__ {size_t op1_use; size_t op2_use; struct TYPE_26__* op1_use_chain; struct TYPE_26__* op2_use_chain; } ;
typedef  TYPE_5__ zend_ssa_op ;
struct TYPE_27__ {int ops; TYPE_4__* vars; TYPE_1__* var_info; } ;
typedef  TYPE_6__ zend_ssa ;
struct TYPE_24__ {uintptr_t var; } ;
struct TYPE_28__ {scalar_t__ opcode; int op1_type; int op2_type; TYPE_3__ op1; } ;
typedef  TYPE_7__ zend_op ;
typedef  int zend_bool ;
struct TYPE_29__ {TYPE_6__* ssa; TYPE_2__* op_array; int /*<<< orphan*/  instr_dead; } ;
typedef  TYPE_8__ context ;
struct TYPE_25__ {TYPE_5__* use_chain; int /*<<< orphan*/  var; } ;
struct TYPE_23__ {int opcodes; } ;
struct TYPE_22__ {int type; } ;

/* Variables and functions */
 int IS_TMP_VAR ; 
 int IS_VAR ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_REF ; 
 int MAY_BE_RESOURCE ; 
 int MAY_BE_STRING ; 
 scalar_t__ ZEND_CALL_VAR_NUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_CASE ; 
 scalar_t__ ZEND_FREE ; 
 scalar_t__ ZEND_NOP ; 
 int /*<<< orphan*/  is_var_dead (TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  try_remove_var_def (TYPE_8__*,size_t,TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  zend_bitset_excl (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  zend_ssa_remove_instr (TYPE_6__*,TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  zend_ssa_rename_defs_of_instr (TYPE_6__*,TYPE_5__*) ; 

__attribute__((used)) static zend_bool dce_instr(context *ctx, zend_op *opline, zend_ssa_op *ssa_op) {
	zend_ssa *ssa = ctx->ssa;
	int free_var = -1;
	zend_uchar free_var_type;

	if (opline->opcode == ZEND_NOP) {
		return 0;
	}

	/* We mark FREEs as dead, but they're only really dead if the destroyed var is dead */
	if (opline->opcode == ZEND_FREE
			&& (ssa->var_info[ssa_op->op1_use].type & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF))
			&& !is_var_dead(ctx, ssa_op->op1_use)) {
		return 0;
	}

	if ((opline->op1_type & (IS_VAR|IS_TMP_VAR))&& !is_var_dead(ctx, ssa_op->op1_use)) {
		if (!try_remove_var_def(ctx, ssa_op->op1_use, ssa_op->op1_use_chain, opline)) {
			if (ssa->var_info[ssa_op->op1_use].type & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF)
				&& opline->opcode != ZEND_CASE) {
				free_var = ssa_op->op1_use;
				free_var_type = opline->op1_type;
			}
		}
	}
	if ((opline->op2_type & (IS_VAR|IS_TMP_VAR)) && !is_var_dead(ctx, ssa_op->op2_use)) {
		if (!try_remove_var_def(ctx, ssa_op->op2_use, ssa_op->op2_use_chain, opline)) {
			if (ssa->var_info[ssa_op->op2_use].type & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF)) {
				if (free_var >= 0) {
					// TODO: We can't free two vars. Keep instruction alive.
					zend_bitset_excl(ctx->instr_dead, opline - ctx->op_array->opcodes);
					return 0;
				}
				free_var = ssa_op->op2_use;
				free_var_type = opline->op2_type;
			}
		}
	}

	zend_ssa_rename_defs_of_instr(ctx->ssa, ssa_op);
	zend_ssa_remove_instr(ctx->ssa, opline, ssa_op);

	if (free_var >= 0) {
		opline->opcode = ZEND_FREE;
		opline->op1.var = (uintptr_t) ZEND_CALL_VAR_NUM(NULL, ssa->vars[free_var].var);
		opline->op1_type = free_var_type;

		ssa_op->op1_use = free_var;
		ssa_op->op1_use_chain = ssa->vars[free_var].use_chain;
		ssa->vars[free_var].use_chain = ssa_op - ssa->ops;
		return 0;
	}
	return 1;
}