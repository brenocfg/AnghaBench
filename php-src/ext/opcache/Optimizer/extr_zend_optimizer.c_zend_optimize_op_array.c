#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_optimizer_ctx ;
struct TYPE_7__ {scalar_t__ live_range; } ;
typedef  TYPE_1__ zend_op_array ;

/* Variables and functions */
 int /*<<< orphan*/  zend_optimize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_recalc_live_ranges (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_redo_pass_two (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_revert_pass_two (TYPE_1__*) ; 

__attribute__((used)) static void zend_optimize_op_array(zend_op_array      *op_array,
                                   zend_optimizer_ctx *ctx)
{
	/* Revert pass_two() */
	zend_revert_pass_two(op_array);

	/* Do actual optimizations */
	zend_optimize(op_array, ctx);

	/* Redo pass_two() */
	zend_redo_pass_two(op_array);

	if (op_array->live_range) {
		zend_recalc_live_ranges(op_array, NULL);
	}
}