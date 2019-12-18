#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zip_prop_handler ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int /*<<< orphan*/ * prop_handler; } ;
typedef  TYPE_1__ ze_zip_object ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_1__* php_zip_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_zip_property_reader (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_is_true (int /*<<< orphan*/ *) ; 
 int zend_std_has_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_zip_has_property(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
	ze_zip_object *obj;
	zip_prop_handler *hnd = NULL;
	int retval = 0;

	obj = php_zip_fetch_object(object);

	if (obj->prop_handler != NULL) {
		hnd = zend_hash_find_ptr(obj->prop_handler, name);
	}

	if (hnd != NULL) {
		zval tmp, *prop;

		if (type == 2) {
			retval = 1;
		} else if ((prop = php_zip_property_reader(obj, hnd, &tmp)) != NULL) {
			if (type == 1) {
				retval = zend_is_true(&tmp);
			} else if (type == 0) {
				retval = (Z_TYPE(tmp) != IS_NULL);
			}
		}

		zval_ptr_dtor(&tmp);
	} else {
		retval = zend_std_has_property(object, name, type, cache_slot);
	}

	return retval;
}