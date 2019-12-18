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
struct TYPE_5__ {TYPE_2__* ce; int /*<<< orphan*/ * name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_property_info ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_type_to_string_resolved (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void emit_incompatible_property_error(
		const zend_property_info *child, const zend_property_info *parent) {
	zend_string *type_str = zend_type_to_string_resolved(parent->type, parent->ce);
	zend_error_noreturn(E_COMPILE_ERROR,
		"Type of %s::$%s must be %s (as in class %s)",
		ZSTR_VAL(child->ce->name),
		ZSTR_VAL(child->name),
		ZSTR_VAL(type_str),
		ZSTR_VAL(parent->ce->name));
}