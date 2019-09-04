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
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 scalar_t__ IS_CONSTANT_AST ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ UNEXPECTED (int) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 
 scalar_t__ zval_update_constant_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_null_constant(zend_class_entry *scope, zval *default_value)
{
	if (Z_TYPE_P(default_value) == IS_CONSTANT_AST) {
		zval constant;

		ZVAL_COPY(&constant, default_value);
		if (UNEXPECTED(zval_update_constant_ex(&constant, scope) != SUCCESS)) {
			return 0;
		}
		if (Z_TYPE(constant) == IS_NULL) {
			return 1;
		}
		zval_ptr_dtor_nogc(&constant);
	}
	return 0;
}