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
typedef  int /*<<< orphan*/  zend_type ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int ce_flags; struct TYPE_5__* parent; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_TRAIT ; 
 scalar_t__ ZEND_TYPE_ALLOW_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_ENCODE_CE (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * ZEND_TYPE_NAME (int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_lookup_class (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_literal_ci (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static zend_bool zend_resolve_class_type(zend_type *type, zend_class_entry *self_ce) {
	zend_class_entry *ce;
	zend_string *name = ZEND_TYPE_NAME(*type);
	if (zend_string_equals_literal_ci(name, "self")) {
		/* We need to explicitly check for this here, to avoid updating the type in the trait and
		 * later using the wrong "self" when the trait is used in a class. */
		if (UNEXPECTED((self_ce->ce_flags & ZEND_ACC_TRAIT) != 0)) {
			zend_throw_error(NULL, "Cannot write a%s value to a 'self' typed static property of a trait", ZEND_TYPE_ALLOW_NULL(*type) ? " non-null" : "");
			return 0;
		}
		ce = self_ce;
	} else if (zend_string_equals_literal_ci(name, "parent")) {
		if (UNEXPECTED(!self_ce->parent)) {
			zend_throw_error(NULL, "Cannot access parent:: when current class scope has no parent");
			return 0;
		}
		ce = self_ce->parent;
	} else {
		ce = zend_lookup_class(name);
		if (UNEXPECTED(!ce)) {
			return 0;
		}
	}

	zend_string_release(name);
	*type = ZEND_TYPE_ENCODE_CE(ce, ZEND_TYPE_ALLOW_NULL(*type));
	return 1;
}