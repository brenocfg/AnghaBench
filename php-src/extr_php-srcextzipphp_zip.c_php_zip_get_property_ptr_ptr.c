#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zip_prop_handler ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/ * prop_handler; } ;
typedef  TYPE_1__ ze_zip_object ;

/* Variables and functions */
 TYPE_1__* php_zip_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_property_ptr_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void**) ; 

__attribute__((used)) static zval *php_zip_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
	ze_zip_object *obj;
	zval *retval = NULL;
	zip_prop_handler *hnd = NULL;

	obj = php_zip_fetch_object(object);

	if (obj->prop_handler != NULL) {
		hnd = zend_hash_find_ptr(obj->prop_handler, name);
	}

	if (hnd == NULL) {
		retval = zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
	}

	return retval;
}