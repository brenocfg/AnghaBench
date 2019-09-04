#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_incomplete_object_handlers ; 
 TYPE_1__* zend_objects_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *php_create_incomplete_object(zend_class_entry *class_type)
{
	zend_object *object;

	object = zend_objects_new( class_type);
	object->handlers = &php_incomplete_object_handlers;

	object_properties_init(object, class_type);

	return object;
}