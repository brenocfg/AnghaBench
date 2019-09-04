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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  xmlreader_prop_handler ;
struct TYPE_3__ {int /*<<< orphan*/ * prop_handler; } ;
typedef  TYPE_1__ xmlreader_object ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* php_xmlreader_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_write_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

zval *xmlreader_write_property(zend_object *object, zend_string *name, zval *value, void **cache_slot)
{
	xmlreader_object *obj;
	xmlreader_prop_handler *hnd = NULL;

	obj = php_xmlreader_fetch_object(object);

	if (obj->prop_handler != NULL) {
		hnd = zend_hash_find_ptr(obj->prop_handler, name);
	}
	if (hnd != NULL) {
		php_error_docref(NULL, E_WARNING, "Cannot write to read-only property");
	} else {
		value = zend_std_write_property(object, name, value, cache_slot);
	}

	return value;
}