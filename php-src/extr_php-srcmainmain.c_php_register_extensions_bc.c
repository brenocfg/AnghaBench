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
typedef  int /*<<< orphan*/  zend_module_entry ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/ * zend_register_internal_module (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_register_extensions_bc(zend_module_entry *ptr, int count)
{
	while (count--) {
		if (zend_register_internal_module(ptr++) == NULL) {
			return FAILURE;
 		}
	}
	return SUCCESS;
}