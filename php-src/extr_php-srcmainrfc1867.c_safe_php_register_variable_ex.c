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
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  is_protected_variable (char*) ; 
 int /*<<< orphan*/  php_register_variable_ex (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void safe_php_register_variable_ex(char *var, zval *val, zval *track_vars_array, zend_bool override_protection) /* {{{ */
{
	if (override_protection || !is_protected_variable(var)) {
		php_register_variable_ex(var, val, track_vars_array);
	}
}