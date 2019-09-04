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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_get_use_type_str (int /*<<< orphan*/ ) ; 
 scalar_t__ zend_string_equals_ci (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_check_already_in_use(uint32_t type, zend_string *old_name, zend_string *new_name, zend_string *check_name) /* {{{ */
{
	if (zend_string_equals_ci(old_name, check_name)) {
		return;
	}

	zend_error_noreturn(E_COMPILE_ERROR, "Cannot use%s %s as %s because the name "
		"is already in use", zend_get_use_type_str(type), ZSTR_VAL(old_name), ZSTR_VAL(new_name));
}