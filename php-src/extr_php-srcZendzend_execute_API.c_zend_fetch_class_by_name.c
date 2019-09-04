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
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int ZEND_FETCH_CLASS_INTERFACE ; 
 int ZEND_FETCH_CLASS_MASK ; 
 int ZEND_FETCH_CLASS_NO_AUTOLOAD ; 
 int ZEND_FETCH_CLASS_SILENT ; 
 int ZEND_FETCH_CLASS_TRAIT ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/ * zend_lookup_class_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_throw_or_error (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

zend_class_entry *zend_fetch_class_by_name(zend_string *class_name, zend_string *key, int fetch_type) /* {{{ */
{
	zend_class_entry *ce;

	if (fetch_type & ZEND_FETCH_CLASS_NO_AUTOLOAD) {
		return zend_lookup_class_ex(class_name, key, 0);
	} else if ((ce = zend_lookup_class_ex(class_name, key, 1)) == NULL) {
		if ((fetch_type & ZEND_FETCH_CLASS_SILENT) == 0 && !EG(exception)) {
			if ((fetch_type & ZEND_FETCH_CLASS_MASK) == ZEND_FETCH_CLASS_INTERFACE) {
				zend_throw_or_error(fetch_type, NULL, "Interface '%s' not found", ZSTR_VAL(class_name));
			} else if ((fetch_type & ZEND_FETCH_CLASS_MASK) == ZEND_FETCH_CLASS_TRAIT) {
				zend_throw_or_error(fetch_type, NULL, "Trait '%s' not found", ZSTR_VAL(class_name));
			} else {
				zend_throw_or_error(fetch_type, NULL, "Class '%s' not found", ZSTR_VAL(class_name));
			}
		}
		return NULL;
	}
	return ce;
}