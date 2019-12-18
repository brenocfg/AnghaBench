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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_is_reserved_class_name (int /*<<< orphan*/  const*) ; 

void zend_assert_valid_class_name(const zend_string *name) /* {{{ */
{
	if (zend_is_reserved_class_name(name)) {
		zend_error_noreturn(E_COMPILE_ERROR,
			"Cannot use '%s' as class name as it is reserved", ZSTR_VAL(name));
	}
}