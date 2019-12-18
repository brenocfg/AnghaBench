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
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  empty_partial_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  join_hash_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int join_partial_arrays(zval *a, zval *b)
{
	zval ret;

	if ((Z_TYPE_P(a) != IS_ARRAY && !IS_PARTIAL_ARRAY(a))
			|| (Z_TYPE_P(b) != IS_ARRAY && !IS_PARTIAL_ARRAY(b))) {
		return FAILURE;
	}

	empty_partial_array(&ret);
	join_hash_tables(Z_ARRVAL(ret), Z_ARRVAL_P(a), Z_ARRVAL_P(b));
	zval_ptr_dtor_nogc(a);
	ZVAL_COPY_VALUE(a, &ret);

	return SUCCESS;
}