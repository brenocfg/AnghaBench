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
typedef  scalar_t__ zend_uchar ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ IS_DOUBLE ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ UNEXPECTED (int) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int zend_verify_weak_scalar_type_hint (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool zend_verify_scalar_type_hint(zend_uchar type_hint, zval *arg, zend_bool strict)
{
	if (UNEXPECTED(strict)) {
		/* SSTH Exception: IS_LONG may be accepted as IS_DOUBLE (converted) */
		if (type_hint != IS_DOUBLE || Z_TYPE_P(arg) != IS_LONG) {
			return 0;
		}
	} else if (UNEXPECTED(Z_TYPE_P(arg) == IS_NULL)) {
		/* NULL may be accepted only by nullable hints (this is already checked) */
		return 0;
	}
	return zend_verify_weak_scalar_type_hint(type_hint, arg);
}