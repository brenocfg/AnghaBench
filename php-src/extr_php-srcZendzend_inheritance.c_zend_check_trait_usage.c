#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ce_flags; size_t num_traits; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_TRAIT ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static uint32_t zend_check_trait_usage(zend_class_entry *ce, zend_class_entry *trait, zend_class_entry **traits) /* {{{ */
{
	uint32_t i;

	if (UNEXPECTED((trait->ce_flags & ZEND_ACC_TRAIT) != ZEND_ACC_TRAIT)) {
		zend_error_noreturn(E_COMPILE_ERROR, "Class %s is not a trait, Only traits may be used in 'as' and 'insteadof' statements", ZSTR_VAL(trait->name));
		return 0;
	}

	for (i = 0; i < ce->num_traits; i++) {
		if (traits[i] == trait) {
			return i;
		}
	}
	zend_error_noreturn(E_COMPILE_ERROR, "Required Trait %s wasn't added to %s", ZSTR_VAL(trait->name), ZSTR_VAL(ce->name));
	return 0;
}