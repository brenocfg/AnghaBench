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
typedef  int /*<<< orphan*/  zend_type ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_LONG ; 
 int MAY_BE_DOUBLE ; 
 int MAY_BE_ITERABLE ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_CONTAINS_CODE (int /*<<< orphan*/ ,scalar_t__) ; 
 int ZEND_TYPE_FULL_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool zend_is_valid_default_value(zend_type type, zval *value)
{
	ZEND_ASSERT(ZEND_TYPE_IS_SET(type));
	if (ZEND_TYPE_CONTAINS_CODE(type, Z_TYPE_P(value))) {
		return 1;
	}
	if ((ZEND_TYPE_FULL_MASK(type) & MAY_BE_DOUBLE) && Z_TYPE_P(value) == IS_LONG) {
		/* Integers are allowed as initializers for floating-point values. */
		convert_to_double(value);
		return 1;
	}
	if ((ZEND_TYPE_FULL_MASK(type) & MAY_BE_ITERABLE) && Z_TYPE_P(value) == IS_ARRAY) {
		return 1;
	}
	return 0;
}