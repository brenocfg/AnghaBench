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
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ php_converter_object ;

/* Variables and functions */
 int /*<<< orphan*/  object_properties_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_converter_object_ctor (int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static zend_object *php_converter_create_object(zend_class_entry *ce) {
	php_converter_object *objval = NULL;
	zend_object *retval = php_converter_object_ctor(ce, &objval);

	object_properties_init(&(objval->obj), ce);

	return retval;
}