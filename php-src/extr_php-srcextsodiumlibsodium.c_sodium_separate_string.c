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
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_REFCOUNTED_P (int /*<<< orphan*/ *) ; 
 int Z_REFCOUNT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TRY_DELREF_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sodium_separate_string(zval *zv) {
	ZEND_ASSERT(Z_TYPE_P(zv) == IS_STRING);
	if (!Z_REFCOUNTED_P(zv) || Z_REFCOUNT_P(zv) > 1) {
		zend_string *copy = zend_string_init(Z_STRVAL_P(zv), Z_STRLEN_P(zv), 0);
		Z_TRY_DELREF_P(zv);
		ZVAL_STR(zv, copy);
	}
}