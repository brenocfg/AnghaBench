#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {struct TYPE_6__* parent; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNEXPECTED (int) ; 
#define  ZEND_FETCH_CLASS_AUTO 131 
 int ZEND_FETCH_CLASS_DEFAULT ; 
 int ZEND_FETCH_CLASS_INTERFACE ; 
 int ZEND_FETCH_CLASS_MASK ; 
 int ZEND_FETCH_CLASS_NO_AUTOLOAD ; 
#define  ZEND_FETCH_CLASS_PARENT 130 
#define  ZEND_FETCH_CLASS_SELF 129 
 int ZEND_FETCH_CLASS_SILENT ; 
#define  ZEND_FETCH_CLASS_STATIC 128 
 int ZEND_FETCH_CLASS_TRAIT ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_execute_data ; 
 int /*<<< orphan*/  exception ; 
 TYPE_1__* zend_get_called_scope (int /*<<< orphan*/ ) ; 
 int zend_get_class_fetch_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* zend_get_executed_scope () ; 
 TYPE_1__* zend_lookup_class_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_throw_or_error (int,int /*<<< orphan*/ *,char*,...) ; 

zend_class_entry *zend_fetch_class(zend_string *class_name, int fetch_type) /* {{{ */
{
	zend_class_entry *ce, *scope;
	int fetch_sub_type = fetch_type & ZEND_FETCH_CLASS_MASK;

check_fetch_type:
	switch (fetch_sub_type) {
		case ZEND_FETCH_CLASS_SELF:
			scope = zend_get_executed_scope();
			if (UNEXPECTED(!scope)) {
				zend_throw_or_error(fetch_type, NULL, "Cannot access self:: when no class scope is active");
			}
			return scope;
		case ZEND_FETCH_CLASS_PARENT:
			scope = zend_get_executed_scope();
			if (UNEXPECTED(!scope)) {
				zend_throw_or_error(fetch_type, NULL, "Cannot access parent:: when no class scope is active");
				return NULL;
			}
			if (UNEXPECTED(!scope->parent)) {
				zend_throw_or_error(fetch_type, NULL, "Cannot access parent:: when current class scope has no parent");
			}
			return scope->parent;
		case ZEND_FETCH_CLASS_STATIC:
			ce = zend_get_called_scope(EG(current_execute_data));
			if (UNEXPECTED(!ce)) {
				zend_throw_or_error(fetch_type, NULL, "Cannot access static:: when no class scope is active");
				return NULL;
			}
			return ce;
		case ZEND_FETCH_CLASS_AUTO: {
				fetch_sub_type = zend_get_class_fetch_type(class_name);
				if (UNEXPECTED(fetch_sub_type != ZEND_FETCH_CLASS_DEFAULT)) {
					goto check_fetch_type;
				}
			}
			break;
	}

	if (fetch_type & ZEND_FETCH_CLASS_NO_AUTOLOAD) {
		return zend_lookup_class_ex(class_name, NULL, fetch_type);
	} else if ((ce = zend_lookup_class_ex(class_name, NULL, fetch_type)) == NULL) {
		if (!(fetch_type & ZEND_FETCH_CLASS_SILENT) && !EG(exception)) {
			if (fetch_sub_type == ZEND_FETCH_CLASS_INTERFACE) {
				zend_throw_or_error(fetch_type, NULL, "Interface '%s' not found", ZSTR_VAL(class_name));
			} else if (fetch_sub_type == ZEND_FETCH_CLASS_TRAIT) {
				zend_throw_or_error(fetch_type, NULL, "Trait '%s' not found", ZSTR_VAL(class_name));
			} else {
				zend_throw_or_error(fetch_type, NULL, "Class '%s' not found", ZSTR_VAL(class_name));
			}
		}
		return NULL;
	}
	return ce;
}