#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  IS_PARTIAL_OBJECT (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  empty_partial_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  join_hash_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int join_partial_objects(zval *a, zval *b)
{
	zval ret;

	if (!IS_PARTIAL_OBJECT(a) || !IS_PARTIAL_OBJECT(b)) {
		return FAILURE;
	}

	empty_partial_object(&ret);
	join_hash_tables(Z_ARRVAL(ret), Z_ARRVAL_P(a), Z_ARRVAL_P(b));
	zval_ptr_dtor_nogc(a);
	ZVAL_COPY_VALUE(a, &ret);

	return SUCCESS;
}