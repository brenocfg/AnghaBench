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
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int ZEND_FETCH_CLASS_EXCEPTION ; 
 int ZEND_FETCH_CLASS_INTERFACE ; 
 int ZEND_FETCH_CLASS_MASK ; 
 int ZEND_FETCH_CLASS_NO_AUTOLOAD ; 
 int ZEND_FETCH_CLASS_SILENT ; 
 int ZEND_FETCH_CLASS_TRAIT ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Z_ADDREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  zend_clear_exception () ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_lookup_class_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_throw_or_error (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ *) ; 

zend_class_entry *zend_fetch_class_by_name(zend_string *class_name, zend_string *key, int fetch_type) /* {{{ */
{
	zend_class_entry *ce;

	if (fetch_type & ZEND_FETCH_CLASS_NO_AUTOLOAD) {
		return zend_lookup_class_ex(class_name, key, fetch_type);
	} else if ((ce = zend_lookup_class_ex(class_name, key, fetch_type)) == NULL) {
		if (fetch_type & ZEND_FETCH_CLASS_SILENT) {
			return NULL;
		}
		if (EG(exception)) {
			if (!(fetch_type & ZEND_FETCH_CLASS_EXCEPTION)) {
				zend_string *exception_str;
				zval exception_zv;
				ZVAL_OBJ(&exception_zv, EG(exception));
				Z_ADDREF(exception_zv);
				zend_clear_exception();
				exception_str = zval_get_string(&exception_zv);
				zend_error_noreturn(E_ERROR,
					"During class fetch: Uncaught %s", ZSTR_VAL(exception_str));
			}
			return NULL;
		}
		if ((fetch_type & ZEND_FETCH_CLASS_MASK) == ZEND_FETCH_CLASS_INTERFACE) {
			zend_throw_or_error(fetch_type, NULL, "Interface '%s' not found", ZSTR_VAL(class_name));
		} else if ((fetch_type & ZEND_FETCH_CLASS_MASK) == ZEND_FETCH_CLASS_TRAIT) {
			zend_throw_or_error(fetch_type, NULL, "Trait '%s' not found", ZSTR_VAL(class_name));
		} else {
			zend_throw_or_error(fetch_type, NULL, "Class '%s' not found", ZSTR_VAL(class_name));
		}
		return NULL;
	}
	return ce;
}