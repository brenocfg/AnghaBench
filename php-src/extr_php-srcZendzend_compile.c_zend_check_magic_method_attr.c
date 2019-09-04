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
typedef  scalar_t__ zend_bool ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int ZEND_ACC_PUBLIC ; 
 int ZEND_ACC_STATIC ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void zend_check_magic_method_attr(uint32_t attr, const char* method, zend_bool is_static) /* {{{ */
{
	if (is_static) {
		if (!(attr & ZEND_ACC_PUBLIC) || !(attr & ZEND_ACC_STATIC)) {
			zend_error(E_WARNING, "The magic method %s() must have public visibility and be static", method);
		}
	} else if (!(attr & ZEND_ACC_PUBLIC) || (attr & ZEND_ACC_STATIC)) {
		zend_error(E_WARNING,
				"The magic method %s() must have public visibility and cannot be static",
				method);
	}
}