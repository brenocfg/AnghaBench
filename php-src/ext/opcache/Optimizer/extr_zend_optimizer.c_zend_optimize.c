#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int debug_level; int optimization_level; } ;
typedef  TYPE_1__ zend_optimizer_ctx ;
struct TYPE_24__ {scalar_t__ type; } ;
typedef  TYPE_2__ zend_op_array ;

/* Variables and functions */
 int ZEND_DUMP_AFTER_OPTIMIZER ; 
 int ZEND_DUMP_AFTER_PASS_1 ; 
 int ZEND_DUMP_AFTER_PASS_10 ; 
 int ZEND_DUMP_AFTER_PASS_11 ; 
 int ZEND_DUMP_AFTER_PASS_13 ; 
 int ZEND_DUMP_AFTER_PASS_3 ; 
 int ZEND_DUMP_AFTER_PASS_4 ; 
 int ZEND_DUMP_AFTER_PASS_5 ; 
 int ZEND_DUMP_AFTER_PASS_6 ; 
 int ZEND_DUMP_AFTER_PASS_9 ; 
 int ZEND_DUMP_BEFORE_OPTIMIZER ; 
 int /*<<< orphan*/  ZEND_DUMP_LIVE_RANGES ; 
 scalar_t__ ZEND_EVAL_CODE ; 
 int ZEND_OPTIMIZER_PASS_1 ; 
 int ZEND_OPTIMIZER_PASS_10 ; 
 int ZEND_OPTIMIZER_PASS_11 ; 
 int ZEND_OPTIMIZER_PASS_13 ; 
 int ZEND_OPTIMIZER_PASS_3 ; 
 int ZEND_OPTIMIZER_PASS_4 ; 
 int ZEND_OPTIMIZER_PASS_5 ; 
 int ZEND_OPTIMIZER_PASS_6 ; 
 int ZEND_OPTIMIZER_PASS_7 ; 
 int ZEND_OPTIMIZER_PASS_9 ; 
 int /*<<< orphan*/  zend_dump_op_array (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_optimize_cfg (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimize_dfa (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimize_func_calls (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimize_temporary_variables (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimizer_compact_literals (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimizer_compact_vars (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_optimizer_nop_removal (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_optimizer_pass1 (TYPE_2__*,TYPE_1__*) ; 
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

	/* pass 1 (Simple local optimizations)
	 * - persistent constant substitution (true, false, null, etc)
	 * - constant casting (ADD expects numbers, CONCAT strings, etc)
	 * - constant expression evaluation
	 * - optimize constant conditional JMPs
	 * - pre-evaluate constant function calls
	 * - eliminate FETCH $GLOBALS followed by FETCH_DIM/UNSET_DIM/ISSET_ISEMPTY_DIM
	 */
	if (ZEND_OPTIMIZER_PASS_1 & ctx->optimization_level) {
		zend_optimizer_pass1(op_array, ctx);
		if (ctx->debug_level & ZEND_DUMP_AFTER_PASS_1) {
			zend_dump_op_array(op_array, 0, "after pass 1", NULL);
		}
	}

	/* pass 3: (Jump optimization)
	 * - optimize series of JMPs
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