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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {scalar_t__ type; int ce_flags; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_CONSTANTS_UPDATED ; 
 int ZEND_ACC_PROPERTY_TYPES_RESOLVED ; 
 scalar_t__ ZEND_INTERNAL_CLASS ; 
 int /*<<< orphan*/  class_table ; 
 TYPE_1__* zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_class_entry *preload_fetch_resolved_ce(zend_string *name, zend_class_entry *self_ce) {
	zend_string *lcname = zend_string_tolower(name);
	zend_class_entry *ce = zend_hash_find_ptr(EG(class_table), lcname);
	zend_string_release(lcname);
	if (!ce) {
		return NULL;
	}
	if (ce == self_ce) {
		/* Ignore the following requirements if this is the class referring to itself */
		return ce;
	}
#ifdef ZEND_WIN32
	/* On Windows we can't link with internal class, because of ASLR */
	if (ce->type == ZEND_INTERNAL_CLASS) {
		return NULL;
	}
#endif
	if (!(ce->ce_flags & ZEND_ACC_CONSTANTS_UPDATED)) {
		return NULL;
	}
	if (!(ce->ce_flags & ZEND_ACC_PROPERTY_TYPES_RESOLVED)) {
		return NULL;
	}
	return ce;
}