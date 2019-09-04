#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_property_info ;
struct TYPE_8__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ zend_class_entry ;
typedef  int zend_bool ;

/* Variables and functions */
 scalar_t__ ZEND_TYPE_ALLOW_NULL (scalar_t__) ; 
 TYPE_2__* ZEND_TYPE_CE (scalar_t__) ; 
 scalar_t__ ZEND_TYPE_IS_CE (scalar_t__) ; 
 int /*<<< orphan*/  ZEND_TYPE_IS_CLASS (scalar_t__) ; 
 int /*<<< orphan*/  ZEND_TYPE_NAME (scalar_t__) ; 
 TYPE_2__* zend_lookup_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_resolve_property_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_string_equals_ci (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

zend_bool property_types_compatible(zend_property_info *parent_info, zend_property_info *child_info) {
	zend_string *parent_name, *child_name;
	zend_class_entry *parent_type_ce, *child_type_ce;
	if (parent_info->type == child_info->type) {
		return 1;
	}

	if (!ZEND_TYPE_IS_CLASS(parent_info->type) || !ZEND_TYPE_IS_CLASS(child_info->type) ||
			ZEND_TYPE_ALLOW_NULL(parent_info->type) != ZEND_TYPE_ALLOW_NULL(child_info->type)) {
		return 0;
	}

	parent_name = ZEND_TYPE_IS_CE(parent_info->type)
		? ZEND_TYPE_CE(parent_info->type)->name
		: zend_resolve_property_type(ZEND_TYPE_NAME(parent_info->type), parent_info->ce);
	child_name = ZEND_TYPE_IS_CE(child_info->type)
		? ZEND_TYPE_CE(child_info->type)->name
		: zend_resolve_property_type(ZEND_TYPE_NAME(child_info->type), child_info->ce);
	if (zend_string_equals_ci(parent_name, child_name)) {
		return 1;
	}

	/* Check for class aliases */
	parent_type_ce = ZEND_TYPE_IS_CE(parent_info->type)
		? ZEND_TYPE_CE(parent_info->type)
		: zend_lookup_class(parent_name);
	child_type_ce = ZEND_TYPE_IS_CE(child_info->type)
		? ZEND_TYPE_CE(child_info->type)
		: zend_lookup_class(child_name);
	return parent_type_ce && child_type_ce && parent_type_ce == child_type_ce;
}