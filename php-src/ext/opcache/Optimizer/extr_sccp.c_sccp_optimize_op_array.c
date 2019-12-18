#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_26__ {int vars_count; TYPE_2__* vars; } ;
typedef  TYPE_3__ zend_ssa ;
struct TYPE_27__ {int debug_level; int /*<<< orphan*/  arena; } ;
typedef  TYPE_4__ zend_optimizer_ctx ;
struct TYPE_28__ {int last_var; } ;
typedef  TYPE_5__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_call_info ;
struct TYPE_24__ {int /*<<< orphan*/  mark_feasible_successors; int /*<<< orphan*/  visit_phi; int /*<<< orphan*/  visit_instr; } ;
struct TYPE_30__ {TYPE_1__ handlers; } ;
struct TYPE_29__ {TYPE_9__ scdf; int /*<<< orphan*/ * values; } ;
typedef  TYPE_6__ sccp_ctx ;
struct TYPE_25__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_CV ; 
 scalar_t__ IS_TOP (int /*<<< orphan*/ *) ; 
 int ZEND_DUMP_SCCP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ replace_constant_operands (TYPE_6__*) ; 
 int /*<<< orphan*/  sccp_context_free (TYPE_6__*) ; 
 int /*<<< orphan*/  sccp_context_init (TYPE_4__*,TYPE_6__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sccp_mark_feasible_successors ; 
 int /*<<< orphan*/  sccp_visit_instr ; 
 int /*<<< orphan*/  sccp_visit_phi ; 
 int /*<<< orphan*/  scdf_init (TYPE_4__*,TYPE_9__*,TYPE_5__*,TYPE_3__*) ; 
 scalar_t__ scdf_remove_unreachable_blocks (TYPE_9__*) ; 
 int /*<<< orphan*/  scdf_solve (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  scp_dump_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 void* zend_arena_checkpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_arena_release (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zend_dump_op_array_name (TYPE_5__*) ; 
 int /*<<< orphan*/  zend_dump_var (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sccp_optimize_op_array(zend_optimizer_ctx *ctx, zend_op_array *op_array, zend_ssa *ssa, zend_call_info **call_map)
{
	sccp_ctx sccp;
	int removed_ops = 0;
	void *checkpoint = zend_arena_checkpoint(ctx->arena);

	sccp_context_init(ctx, &sccp, ssa, op_array, call_map);

	sccp.scdf.handlers.visit_instr = sccp_visit_instr;
	sccp.scdf.handlers.visit_phi = sccp_visit_phi;
	sccp.scdf.handlers.mark_feasible_successors = sccp_mark_feasible_successors;

	scdf_init(ctx, &sccp.scdf, op_array, ssa);
	scdf_solve(&sccp.scdf, "SCCP");

	if (ctx->debug_level & ZEND_DUMP_SCCP) {
		int i, first = 1;

		for (i = op_array->last_var; i < ssa->vars_count; i++) {
			zval *zv = &sccp.values[i];

			if (IS_TOP(zv) || IS_BOT(zv)) {
				continue;
			}
			if (first) {
				first = 0;
				fprintf(stderr, "\nSCCP Values for \"");
				zend_dump_op_array_name(op_array);
				fprintf(stderr, "\":\n");
			}
			fprintf(stderr, "    #%d.", i);
			zend_dump_var(op_array, IS_CV, ssa->vars[i].var);
			fprintf(stderr, " =");
			scp_dump_value(zv);
			fprintf(stderr, "\n");
		}
	}

	removed_ops += scdf_remove_unreachable_blocks(&sccp.scdf);
	removed_ops += replace_constant_operands(&sccp);

	sccp_context_free(&sccp);
	zend_arena_release(&ctx->arena, checkpoint);

	return removed_ops;
}