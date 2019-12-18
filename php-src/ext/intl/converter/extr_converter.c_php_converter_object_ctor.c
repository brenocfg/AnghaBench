#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_9__ {TYPE_1__ obj; int /*<<< orphan*/  error; } ;
typedef  TYPE_2__ php_converter_object ;

/* Variables and functions */
 int /*<<< orphan*/  intl_error_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_converter_object_handlers ; 
 TYPE_2__* zend_object_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *php_converter_object_ctor(zend_class_entry *ce, php_converter_object **pobjval) {
	php_converter_object *objval;

	objval = zend_object_alloc(sizeof(php_converter_object), ce);

	zend_object_std_init(&objval->obj, ce);
	object_properties_init(&objval->obj, ce);
	intl_error_init(&(objval->error));

	objval->obj.handlers = &php_converter_object_handlers;
	*pobjval = objval;

	return &objval->obj;
}