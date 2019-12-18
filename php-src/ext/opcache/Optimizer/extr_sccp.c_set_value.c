#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {TYPE_2__* ssa; int /*<<< orphan*/  op_array; } ;
typedef  TYPE_3__ scdf_ctx ;
struct TYPE_11__ {int /*<<< orphan*/ * values; } ;
typedef  TYPE_4__ sccp_ctx ;
struct TYPE_9__ {TYPE_1__* vars; } ;
struct TYPE_8__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_CV ; 
 scalar_t__ IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_TOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  scdf_add_to_worklist (TYPE_3__*,int) ; 
 int /*<<< orphan*/  scp_dump_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_is_identical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_value(scdf_ctx *scdf, sccp_ctx *ctx, int var, zval *new) {
	zval *value = &ctx->values[var];
	if (IS_BOT(value) || IS_TOP(new)) {
		return;
	}

#if SCP_DEBUG
	fprintf(stderr, "Lowering #%d.", var);
	zend_dump_var(scdf->op_array, IS_CV, scdf->ssa->vars[var].var);
	fprintf(stderr, " from");
	scp_dump_value(value);
	fprintf(stderr, " to");
	scp_dump_value(new);
	fprintf(stderr, "\n");
#endif

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