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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_FINAL ; 
 int ZEND_ACC_STATIC ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void zend_check_const_and_trait_alias_attr(uint32_t attr, const char* entity) /* {{{ */
{
	if (attr & ZEND_ACC_STATIC) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot use 'static' as %s modifier", entity);
	} else if (attr & ZEND_ACC_ABSTRACT) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot use 'abstract' as %s modifier", entity);
	} else if (attr & ZEND_ACC_FINAL) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot use 'final' as %s modifier", entity);
	}
}