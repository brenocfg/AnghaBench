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
struct TYPE_3__ {scalar_t__ constants; int /*<<< orphan*/  arena; } ;
typedef  TYPE_1__ zend_optimizer_ctx ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_arena_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_hash_add (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_init (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_optimizer_zval_dtor_wrapper ; 

void zend_optimizer_collect_constant(zend_optimizer_ctx *ctx, zval *name, zval* value)
{
	zval val;

	if (!ctx->constants) {
		ctx->constants = zend_arena_alloc(&ctx->arena, sizeof(HashTable));
		zend_hash_init(ctx->constants, 16, NULL, zend_optimizer_zval_dtor_wrapper, 0);
	}
	ZVAL_COPY(&val, value);
	zend_hash_add(ctx->constants, Z_STR_P(name), &val);
}