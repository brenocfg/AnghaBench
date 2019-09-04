#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int debug_level; int optimization_level; } ;
typedef  TYPE_1__ zend_optimizer_ctx ;
struct TYPE_23__ {scalar_t__ type; } ;
typedef  TYPE_2__ zend_op_array ;

/* Variables and functions */
 int ZEND_DUMP_AFTER_OPTIMIZER ; 
 int ZEND_DUMP_AFTER_PASS_1 ; 
 int ZEND_DUMP_AFTER_PASS_10 ; 
 int ZEND_DUMP_AFTER_PASS_11 ; 
 int ZEND_DUMP_AFTER_PASS_13 ; 
 int ZEND_DUMP_AFTER_PASS_2 ; 
 int ZEND_DUMP_AFTER_PASS_3 ; 
 int ZEND_DUMP_AFTER_PASS_4 ; 
 int ZEND_DUMP_AFTER_PASS_5 ; 
 int ZEND_DUMP_AFTER_PASS_9 ; 
 int ZEND_DUMP_BEFORE_OPTIMIZER ; 
 int /*<<< orphan*/  ZEND_DUMP_LIVE_RANGES ; 
 scalar_t__ ZEND_EVAL_CODE ; 
 int ZEND_OPTIMIZER_PASS_1 ; 
 int ZEND_OPTIMIZER_PASS_10 ; 
 int ZEND_OPTIMIZER_PASS_11 ; 
 int ZEND_OPTIMIZER_PASS_13 ; 
 int ZEND_OPTIMIZER_PASS_2 ; 
 int ZEND_OPTIMIZER_PASS_3 ; 
 int ZEND_OPTIMIZER_PASS_4 ; 
 int ZEND_OPTIMIZER_PASS_5 ; 
 int ZEND_OPTIMIZER_PASS_6 ; 
 int ZEND_OPTIMIZER_PASS_7 ; 
 int ZEND_OPTIMIZER_PASS_9 ; 
 int /*<<< orphan*/  zend_dump_op_array (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_optimize_cfg (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimize_func_calls (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimize_temporary_variables (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimizer_compact_literals (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimizer_compact_vars (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_optimizer_nop_removal (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimizer_pass1 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimizer_pass2 (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_optimizer_pass3 (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void zend_optimize(zend_op_array      *op_array,
                          zend_optimizer_ctx *ctx)
{
	if (op_array->type == ZEND_EVAL_CODE) {
		return;
	}

	if (ctx->debug_level & ZEND_DUMP_BEFORE_OPTIMIZER) {
		zend_dump_op_array(op_array, ZEND_DUMP_LIVE_RANGES, "before optimizer", NULL);
	}

	/* pass 1
	 * - substitute persistent constants (true, false, null, etc)
	 * - perform compile-time evaluation of constant binary and unary operations
	 * - optimize series of ADD_STRING and/or ADD_CHAR
	 * - convert CAST(IS_BOOL,x) into BOOL(x)
         * - pre-evaluate constant function calls
	 */
	if (ZEND_OPTIMIZER_PASS_1 & ctx->optimization_level) {
		zend_optimizer_pass1(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_1) {
			zend_dump_op_array(op_array, 0, "after pass 1", NULL);
		}
	}

	/* pass 2:
	 * - convert non-numeric constants to numeric constants in numeric operators
	 * - optimize constant conditional JMPs
	 */
	if (ZEND_OPTIMIZER_PASS_2 & ctx->optimization_level) {
		zend_optimizer_pass2(op_array);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_2) {
			zend_dump_op_array(op_array, 0, "after pass 2", NULL);
		}
	}

	/* pass 3:
	 * - optimize $i = $i+expr to $i+=expr
	 * - optimize series of JMPs
	 * - change $i++ to ++$i where possible
	 */
	if (ZEND_OPTIMIZER_PASS_3 & ctx->optimization_level) {
		zend_optimizer_pass3(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_3) {
			zend_dump_op_array(op_array, 0, "after pass 3", NULL);
		}
	}

	/* pass 4:
	 * - INIT_FCALL_BY_NAME -> DO_FCALL
	 */
	if (ZEND_OPTIMIZER_PASS_4 & ctx->optimization_level) {
		zend_optimize_func_calls(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_4) {
			zend_dump_op_array(op_array, 0, "after pass 4", NULL);
		}
	}

	/* pass 5:
	 * - CFG optimization
	 */
	if (ZEND_OPTIMIZER_PASS_5 & ctx->optimization_level) {
		zend_optimize_cfg(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_5) {
			zend_dump_op_array(op_array, 0, "after pass 5", NULL);
		}
	}

#if HAVE_DFA_PASS
	/* pass 6:
	 * - DFA optimization
	 */
	if ((ZEND_OPTIMIZER_PASS_6 & ctx->optimization_level) &&
	    !(ZEND_OPTIMIZER_PASS_7 & ctx->optimization_level)) {
		zend_optimize_dfa(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_6) {
			zend_dump_op_array(op_array, 0, "after pass 6", NULL);
		}
	}
#endif

	/* pass 9:
	 * - Optimize temp variables usage
	 */
	if (ZEND_OPTIMIZER_PASS_9 & ctx->optimization_level) {
		zend_optimize_temporary_variables(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_9) {
			zend_dump_op_array(op_array, 0, "after pass 9", NULL);
		}
	}

	/* pass 10:
	 * - remove NOPs
	 */
	if (((ZEND_OPTIMIZER_PASS_10|ZEND_OPTIMIZER_PASS_5) & ctx->optimization_level) == ZEND_OPTIMIZER_PASS_10) {
		zend_optimizer_nop_removal(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_10) {
			zend_dump_op_array(op_array, 0, "after pass 10", NULL);
		}
	}

	/* pass 11:
	 * - Compact literals table
	 */
	if ((ZEND_OPTIMIZER_PASS_11 & ctx->optimization_level) &&
	    (!(ZEND_OPTIMIZER_PASS_6 & ctx->optimization_level) ||
	     !(ZEND_OPTIMIZER_PASS_7 & ctx->optimization_level))) {
		zend_optimizer_compact_literals(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_11) {
			zend_dump_op_array(op_array, 0, "after pass 11", NULL);
		}
	}

	if ((ZEND_OPTIMIZER_PASS_13 & ctx->optimization_level) &&
	    (!(ZEND_OPTIMIZER_PASS_6 & ctx->optimization_level) ||
	     !(ZEND_OPTIMIZER_PASS_7 & ctx->optimization_level))) {
		zend_optimizer_compact_vars(op_array);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_13) {
			zend_dump_op_array(op_array, 0, "after pass 13", NULL);
		}
	}

	if (ZEND_OPTIMIZER_PASS_7 & ctx->optimization_level) {
		return;
	}

	if (ctx->debug_level & ZEND_DUMP_AFTER_OPTIMIZER) {
		zend_dump_op_array(op_array, 0, "after optimizer", NULL);
	}
}