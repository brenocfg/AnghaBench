#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_3__ {int ce_flags; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int ZEND_ACC_HAS_UNLINKED_USES ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Z_ADDREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  zend_clear_exception () ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_unrecoverable_load_failure(zend_class_entry *ce) {
	/* If this class has been used while unlinked through a variance obligation, it is not legal
	 * to remove the class from the class table and throw an exception, because there is already
	 * a dependence on the inheritance hierarchy of this specific class. Instead we fall back to
	 * a fatal error, as would happen if we did not allow exceptions in the first place. */
	if (ce->ce_flags & ZEND_ACC_HAS_UNLINKED_USES) {
		zend_string *exception_str;
		zval exception_zv;
		ZEND_ASSERT(EG(exception) && "Exception must have been thrown");
		ZVAL_OBJ(&exception_zv, EG(exception));
		Z_ADDREF(exception_zv);
		zend_clear_exception();
		exception_str = zval_get_string(&exception_zv);
		zend_error_noreturn(E_ERROR,
			"During inheritance of %s with variance dependencies: Uncaught %s", ZSTR_VAL(ce->name), ZSTR_VAL(exception_str));
	}
}