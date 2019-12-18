#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_12__ {int ce_flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int zend_bool ;
typedef  scalar_t__ inheritance_status ;
typedef  int /*<<< orphan*/  Bucket ;

/* Variables and functions */
 int /*<<< orphan*/  CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 scalar_t__ EXPECTED (int) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ INHERITANCE_SUCCESS ; 
 scalar_t__ INHERITANCE_UNRESOLVED ; 
 scalar_t__ UNEXPECTED (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_EXPLICIT_ABSTRACT_CLASS ; 
 int ZEND_ACC_IMPLICIT_ABSTRACT_CLASS ; 
 int ZEND_ACC_INTERFACE ; 
 int ZEND_ACC_LINKED ; 
 int ZEND_ACC_TRAIT ; 
 int ZEND_ACC_UNRESOLVED_VARIANCE ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_table ; 
 int /*<<< orphan*/  zend_build_properties_info_table (TYPE_1__*) ; 
 scalar_t__ zend_can_early_bind (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_do_inheritance_ex (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_get_object_type (TYPE_1__*) ; 
 int /*<<< orphan*/ * zend_hash_add_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zend_hash_set_bucket_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_verify_abstract_class (TYPE_1__*) ; 

zend_bool zend_try_early_bind(zend_class_entry *ce, zend_class_entry *parent_ce, zend_string *lcname, zval *delayed_early_binding) /* {{{ */
{
	inheritance_status status = zend_can_early_bind(ce, parent_ce);

	if (EXPECTED(status != INHERITANCE_UNRESOLVED)) {
		if (delayed_early_binding) {
			if (UNEXPECTED(zend_hash_set_bucket_key(EG(class_table), (Bucket*)delayed_early_binding, lcname) == NULL)) {
				zend_error_noreturn(E_COMPILE_ERROR, "Cannot declare %s %s, because the name is already in use", zend_get_object_type(ce), ZSTR_VAL(ce->name));
				return 0;
			}
		} else {
			if (UNEXPECTED(zend_hash_add_ptr(CG(class_table), lcname, ce) == NULL)) {
				return 0;
			}
		}
		zend_do_inheritance_ex(ce, parent_ce, status == INHERITANCE_SUCCESS);
		zend_build_properties_info_table(ce);
		if ((ce->ce_flags & (ZEND_ACC_IMPLICIT_ABSTRACT_CLASS|ZEND_ACC_INTERFACE|ZEND_ACC_TRAIT|ZEND_ACC_EXPLICIT_ABSTRACT_CLASS)) == ZEND_ACC_IMPLICIT_ABSTRACT_CLASS) {
			zend_verify_abstract_class(ce);
		}
		ZEND_ASSERT(!(ce->ce_flags & ZEND_ACC_UNRESOLVED_VARIANCE));
		ce->ce_flags |= ZEND_ACC_LINKED;
		return 1;
	}
	return 0;
}