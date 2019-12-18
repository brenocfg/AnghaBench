#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ssa ;
struct TYPE_5__ {int /*<<< orphan*/  arena; } ;
typedef  TYPE_1__ zend_optimizer_ctx ;
typedef  int /*<<< orphan*/  zend_op_array ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 void* zend_arena_checkpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_arena_release (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ zend_dfa_analyze_op_array (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_dfa_optimize_op_array (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void zend_optimize_dfa(zend_op_array *op_array, zend_optimizer_ctx *ctx)
{
	void *checkpoint = zend_arena_checkpoint(ctx->arena);
	zend_ssa ssa;

	if (zend_dfa_analyze_op_array(op_array, ctx, &ssa) != SUCCESS) {
		zend_arena_release(&ctx->arena, checkpoint);
		return;
	}

	zend_dfa_optimize_op_array(op_array, ctx, &ssa, NULL);

	/* Destroy SSA */
	zend_arena_release(&ctx->arena, checkpoint);
}