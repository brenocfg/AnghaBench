#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int ce_flags; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  parent_prop; int /*<<< orphan*/  child_prop; int /*<<< orphan*/  parent_fn; int /*<<< orphan*/  child_fn; TYPE_1__* dependency_ce; } ;
typedef  TYPE_2__ variance_obligation ;
typedef  scalar_t__ inheritance_status ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 scalar_t__ INHERITANCE_ERROR ; 
 scalar_t__ INHERITANCE_SUCCESS ; 
 scalar_t__ INHERITANCE_UNRESOLVED ; 
 scalar_t__ OBLIGATION_COMPATIBILITY ; 
 scalar_t__ OBLIGATION_DEPENDENCY ; 
 scalar_t__ OBLIGATION_PROPERTY_COMPATIBILITY ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_LINKED ; 
 int ZEND_ACC_UNRESOLVED_VARIANCE ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_REMOVE ; 
 TYPE_2__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_incompatible_method_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_incompatible_property_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ property_types_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_delayed_variance_obligations (TYPE_1__*) ; 
 scalar_t__ zend_do_perform_implementation_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_variance_obligation(zval *zv) {
	variance_obligation *obligation = Z_PTR_P(zv);
	if (obligation->type == OBLIGATION_DEPENDENCY) {
		zend_class_entry *dependency_ce = obligation->dependency_ce;
		if (dependency_ce->ce_flags & ZEND_ACC_UNRESOLVED_VARIANCE) {
			resolve_delayed_variance_obligations(dependency_ce);
		}
		if (!(dependency_ce->ce_flags & ZEND_ACC_LINKED)) {
			return ZEND_HASH_APPLY_KEEP;
		}
	} else if (obligation->type == OBLIGATION_COMPATIBILITY) {
		inheritance_status status = zend_do_perform_implementation_check(
			obligation->child_fn, obligation->parent_fn);
		if (UNEXPECTED(status != INHERITANCE_SUCCESS)) {
			if (EXPECTED(status == INHERITANCE_UNRESOLVED)) {
				return ZEND_HASH_APPLY_KEEP;
			}
			ZEND_ASSERT(status == INHERITANCE_ERROR);
			emit_incompatible_method_error(obligation->child_fn, obligation->parent_fn, status);
		}
		/* Either the compatibility check was successful or only threw a warning. */
	} else {
		ZEND_ASSERT(obligation->type == OBLIGATION_PROPERTY_COMPATIBILITY);
		inheritance_status status =
			property_types_compatible(obligation->parent_prop, obligation->child_prop);
		if (status != INHERITANCE_SUCCESS) {
			if (status == INHERITANCE_UNRESOLVED) {
				return ZEND_HASH_APPLY_KEEP;
			}
			ZEND_ASSERT(status == INHERITANCE_ERROR);
			emit_incompatible_property_error(obligation->child_prop, obligation->parent_prop);
		}
	}
	return ZEND_HASH_APPLY_REMOVE;
}