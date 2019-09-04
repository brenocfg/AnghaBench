#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  scdf_ctx ;
struct TYPE_3__ {int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ sccp_ctx ;

/* Variables and functions */
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_TOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCP_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scdf_add_to_worklist (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_value(scdf_ctx *scdf, sccp_ctx *ctx, int var, zval *new) {
	zval *value = &ctx->values[var];
	if (IS_BOT(value) || IS_TOP(new)) {
		return;
	}

	if (IS_BOT(new)) {
		SCP_DEBUG("Lowering var %d to BOT\n", var);
	} else if (!IS_PARTIAL_ARRAY(new) && !IS_PARTIAL_OBJECT(new)) {
		SCP_DEBUG("Lowering var %d to %Z\n", var, new);
	}

	if (IS_TOP(value) || IS_BOT(new)) {
		zval_ptr_dtor_nogc(value);
		ZVAL_COPY(value, new);
		scdf_add_to_worklist(scdf, var);
		return;
	}

	/* Always replace PARTIAL_(ARRAY|OBJECT), as new maybe changed by join_partial_(arrays|object) */
	if (IS_PARTIAL_ARRAY(new) || IS_PARTIAL_OBJECT(new)) {
		if (Z_TYPE_P(value) != Z_TYPE_P(new)
			|| zend_hash_num_elements(Z_ARR_P(new)) != zend_hash_num_elements(Z_ARR_P(value))) {
			zval_ptr_dtor_nogc(value);
			ZVAL_COPY(value, new);
			scdf_add_to_worklist(scdf, var);
		}
		return;
	}

#if ZEND_DEBUG
	ZEND_ASSERT(zend_is_identical(value, new));
#endif
}