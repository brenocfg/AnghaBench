#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_bool ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  RETURN_FALSE ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _DO_THROW (char*) ; 
 int call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_print_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_printf (char*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reflection_export_impl(zval *return_value, zval *object, zend_bool return_output) {
	zval fname, retval;
	int result;

	/* Invoke the __toString() method */
	ZVAL_STRINGL(&fname, "__tostring", sizeof("__tostring") - 1);
	result = call_user_function(NULL, object, &fname, &retval, 0, NULL);
	zval_ptr_dtor_str(&fname);

	if (result == FAILURE) {
		_DO_THROW("Invocation of method __toString() failed");
		return;
	}

	if (Z_TYPE(retval) == IS_UNDEF) {
		php_error_docref(NULL, E_WARNING, "%s::__toString() did not return anything", ZSTR_VAL(Z_OBJCE_P(object)->name));
		RETURN_FALSE;
	}

	if (return_output) {
		ZVAL_COPY_VALUE(return_value, &retval);
	} else {
		/* No need for _r variant, return of __toString should always be a string */
		zend_print_zval(&retval, 0);
		zend_printf("\n");
		zval_ptr_dtor(&retval);
	}
}