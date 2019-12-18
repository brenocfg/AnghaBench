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
typedef  int /*<<< orphan*/  zend_extension ;

/* Variables and functions */
 int SUCCESS ; 
 scalar_t__ last_resource_number ; 
 scalar_t__ zend_extension_dtor ; 
 int /*<<< orphan*/  zend_extensions ; 
 int /*<<< orphan*/  zend_llist_init (int /*<<< orphan*/ *,int,void (*) (void*),int) ; 
 scalar_t__ zend_op_array_extension_handles ; 

int zend_startup_extensions_mechanism()
{
	/* Startup extensions mechanism */
	zend_llist_init(&zend_extensions, sizeof(zend_extension), (void (*)(void *)) zend_extension_dtor, 1);
	zend_op_array_extension_handles = 0;
	last_resource_number = 0;
	return SUCCESS;
}