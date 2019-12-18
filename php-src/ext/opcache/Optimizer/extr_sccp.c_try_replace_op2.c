#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_17__ {int op2_use; int result_def; int op2_use_chain; } ;
typedef  TYPE_2__ zend_ssa_op ;
struct TYPE_18__ {int opcode; } ;
typedef  TYPE_3__ zend_op ;
typedef  int zend_bool ;
struct TYPE_16__ {TYPE_5__* ssa; int /*<<< orphan*/  op_array; } ;
struct TYPE_19__ {TYPE_1__ scdf; } ;
typedef  TYPE_4__ sccp_ctx ;
struct TYPE_20__ {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_STRING ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_3__*) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
#define  ZEND_FETCH_CLASS 128 
 int ZEND_INSTANCEOF ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ can_replace_op2 (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ zend_optimizer_update_op2_const (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ssa_remove_result_def (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_ssa_unlink_use_chain (TYPE_5__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool try_replace_op2(
		sccp_ctx *ctx, zend_op *opline, zend_ssa_op *ssa_op, int var, zval *value) {
	if (ssa_op->op2_use == var && can_replace_op2(ctx->scdf.op_array, opline, ssa_op)) {
		zval zv;
		ZVAL_COPY(&zv, value);
		if (zend_optimizer_update_op2_const(ctx->scdf.op_array, opline, &zv)) {
			return 1;
		} else {
			switch (opline->opcode) {
				case ZEND_FETCH_CLASS:
					if (Z_TYPE(zv) == IS_STRING) {
						ZEND_ASSERT((opline + 1)->opcode == ZEND_INSTANCEOF);
						ZEND_ASSERT(ssa_op->result_def == (ssa_op + 1)->op2_use);
						if (zend_optimizer_update_op2_const(ctx->scdf.op_array, opline + 1, &zv)) {
							zend_ssa_op *next_op = ssa_op + 1;
							zend_ssa_unlink_use_chain(ctx->scdf.ssa, next_op - ctx->scdf.ssa->ops, next_op->op2_use);
							next_op->op2_use = -1;
							next_op->op2_use_chain = -1;
							zend_ssa_remove_result_def(ctx->scdf.ssa, ssa_op);
							MAKE_NOP(opline);
							return 1;
						}
					}
				default:
					break;
			}
			zval_ptr_dtor_nogc(&zv);
		}
	}
	return 0;
}