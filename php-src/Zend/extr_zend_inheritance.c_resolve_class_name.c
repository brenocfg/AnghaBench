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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_6__ {int ce_flags; int /*<<< orphan*/ * name; int /*<<< orphan*/ * parent_name; TYPE_1__* parent; } ;
typedef  TYPE_2__ zend_class_entry ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ZEND_ACC_RESOLVED_PARENT ; 
 int /*<<< orphan*/  ZEND_ASSERT (TYPE_2__*) ; 
 scalar_t__ zend_string_equals_literal_ci (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static zend_string *resolve_class_name(zend_class_entry *scope, zend_string *name) {
	ZEND_ASSERT(scope);
	if (zend_string_equals_literal_ci(name, "parent") && scope->parent) {
		if (scope->ce_flags & ZEND_ACC_RESOLVED_PARENT) {
			return scope->parent->name;
		} else {
			return scope->parent_name;
		}
	} else if (zend_string_equals_literal_ci(name, "self")) {
		return scope->name;
	} else {
		return name;
	}
}