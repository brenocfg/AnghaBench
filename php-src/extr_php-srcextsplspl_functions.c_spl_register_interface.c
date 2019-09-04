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
typedef  int /*<<< orphan*/  zend_function_entry ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CLASS_ENTRY_EX (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_register_internal_interface (int /*<<< orphan*/ *) ; 

void spl_register_interface(zend_class_entry ** ppce, char * class_name, const zend_function_entry * functions)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY_EX(ce, class_name, strlen(class_name), functions);
	*ppce = zend_register_internal_interface(&ce);
}