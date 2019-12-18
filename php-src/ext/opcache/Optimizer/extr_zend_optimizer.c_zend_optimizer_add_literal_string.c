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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_op_array ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_optimizer_add_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_hash_val (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int zend_optimizer_add_literal_string(zend_op_array *op_array, zend_string *str) {
	zval zv;
	ZVAL_STR(&zv, str);
	zend_string_hash_val(str);
	return zend_optimizer_add_literal(op_array, &zv);
}