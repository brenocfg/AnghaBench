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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_property_info ;
struct TYPE_5__ {TYPE_1__* ce; int /*<<< orphan*/ * properties_table; } ;
typedef  TYPE_2__ zend_object ;
struct TYPE_4__ {intptr_t default_properties_count; int /*<<< orphan*/ ** properties_info_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 

__attribute__((used)) static inline zend_property_info *zend_get_property_info_for_slot(zend_object *obj, zval *slot)
{
	zend_property_info **table = obj->ce->properties_info_table;
	intptr_t prop_num = slot - obj->properties_table;
	ZEND_ASSERT(prop_num >= 0 && prop_num < obj->ce->default_properties_count);
	return table[prop_num];
}