#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  zend_declare_property_null (int /*<<< orphan*/ *,char*,int,int) ; 

void spl_register_property( zend_class_entry * class_entry, char *prop_name, int prop_name_len, int prop_flags)
{
	zend_declare_property_null(class_entry, prop_name, prop_name_len, prop_flags);
}