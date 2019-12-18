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
typedef  int /*<<< orphan*/  ser_context ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/  const*) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  do_from_zval_err (int /*<<< orphan*/ *,char*,char*) ; 
 int zend_hash_num_elements (int /*<<< orphan*/ ) ; 

size_t calculate_scm_rights_space(const zval *arr, ser_context *ctx)
{
	int num_elems;

	if (Z_TYPE_P(arr) != IS_ARRAY) {
		do_from_zval_err(ctx, "%s", "expected an array here");
		return (size_t)-1;
	}

	num_elems = zend_hash_num_elements(Z_ARRVAL_P(arr));
	if (num_elems == 0) {
		do_from_zval_err(ctx, "%s", "expected at least one element in this array");
		return (size_t)-1;
	}

	return zend_hash_num_elements(Z_ARRVAL_P(arr)) * sizeof(int);
}