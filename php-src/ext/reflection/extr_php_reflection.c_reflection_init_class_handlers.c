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
struct TYPE_3__ {int /*<<< orphan*/  unserialize; int /*<<< orphan*/  serialize; int /*<<< orphan*/  create_object; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  reflection_objects_new ; 
 int /*<<< orphan*/  zend_class_serialize_deny ; 
 int /*<<< orphan*/  zend_class_unserialize_deny ; 

__attribute__((used)) static void reflection_init_class_handlers(zend_class_entry *ce) {
	ce->create_object = reflection_objects_new;
	ce->serialize = zend_class_serialize_deny;
	ce->unserialize = zend_class_unserialize_deny;
}