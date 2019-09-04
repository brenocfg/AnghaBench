#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_5__ {int /*<<< orphan*/ * name; TYPE_1__* parent; } ;
typedef  TYPE_2__ zend_class_entry ;
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ zend_string_equals_literal_ci (int /*<<< orphan*/ *,char*) ; 

zend_string* zend_resolve_property_type(zend_string *type, zend_class_entry *scope) /* {{{ */
{
	if (zend_string_equals_literal_ci(type, "parent")) {
		if (scope && scope->parent) {
			return scope->parent->name;
		}
	}

	if (zend_string_equals_literal_ci(type, "self")) {
		if (scope) {
			return scope->name;
		}
	}

	return type;
}