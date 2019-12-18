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

/* Variables and functions */
 int /*<<< orphan*/  GC_ADDREF (int /*<<< orphan*/ *) ; 
 int GC_FLAGS (int /*<<< orphan*/ *) ; 
 int GC_PERSISTENT ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_REFCOUNTED_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void browscap_zval_copy_ctor(zval *p) /* {{{ */
{
	if (Z_REFCOUNTED_P(p)) {
		zend_string *str;

		ZEND_ASSERT(Z_TYPE_P(p) == IS_STRING);
		str = Z_STR_P(p);
		if (!(GC_FLAGS(str) & GC_PERSISTENT)) {
			GC_ADDREF(str);
		} else {
			ZVAL_NEW_STR(p, zend_string_init(ZSTR_VAL(str), ZSTR_LEN(str), 0));
		}
	}
}