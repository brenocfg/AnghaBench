#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_property_info ;

/* Variables and functions */
 scalar_t__ ZEND_TYPE_IS_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* pemalloc (int,int) ; 
 int /*<<< orphan*/  zend_string_addref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_property_info *zend_duplicate_property_info_internal(zend_property_info *property_info) /* {{{ */
{
	zend_property_info* new_property_info = pemalloc(sizeof(zend_property_info), 1);
	memcpy(new_property_info, property_info, sizeof(zend_property_info));
	zend_string_addref(new_property_info->name);
	if (ZEND_TYPE_IS_NAME(new_property_info->type)) {
		zend_string_addref(ZEND_TYPE_NAME(new_property_info->type));
	}

	return new_property_info;
}