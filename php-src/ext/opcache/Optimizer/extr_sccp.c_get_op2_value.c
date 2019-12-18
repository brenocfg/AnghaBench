#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_11__ {int op2_use; } ;
typedef  TYPE_3__ zend_ssa_op ;
struct TYPE_10__ {int /*<<< orphan*/  constant; } ;
struct TYPE_12__ {scalar_t__ op2_type; TYPE_2__ op2; } ;
typedef  TYPE_4__ zend_op ;
struct TYPE_9__ {int /*<<< orphan*/  op_array; } ;
struct TYPE_13__ {int /*<<< orphan*/ * values; TYPE_1__ scdf; } ;
typedef  TYPE_5__ sccp_ctx ;

/* Variables and functions */
 int /*<<< orphan*/ * CT_CONSTANT_EX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CONST ; 

__attribute__((used)) static zval *get_op2_value(sccp_ctx *ctx, zend_op *opline, zend_ssa_op *ssa_op) {
	if (opline->op2_type == IS_CONST) {
		return CT_CONSTANT_EX(ctx->scdf.op_array, opline->op2.constant);
	} else if (ssa_op->op2_use != -1) {
		return &ctx->values[ssa_op->op2_use];
	} else {
		return NULL;
	}
}