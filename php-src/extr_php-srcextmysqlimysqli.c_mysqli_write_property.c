#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_6__ {int /*<<< orphan*/  (* write_func ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ mysqli_prop_handler ;
struct TYPE_7__ {int /*<<< orphan*/ * prop_handler; } ;
typedef  TYPE_2__ mysqli_object ;

/* Variables and functions */
 TYPE_2__* php_mysqli_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_write_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

zval *mysqli_write_property(zend_object *object, zend_string *name, zval *value, void **cache_slot)
{
	mysqli_object *obj;
	mysqli_prop_handler *hnd = NULL;

	obj = php_mysqli_fetch_object(object);

	if (obj->prop_handler != NULL) {
		hnd = zend_hash_find_ptr(obj->prop_handler, name);
	}

	if (hnd) {
		hnd->write_func(obj, value);
	} else {
		value = zend_std_write_property(object, name, value, cache_slot);
	}

	return value;
}