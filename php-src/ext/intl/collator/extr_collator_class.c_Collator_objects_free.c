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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int /*<<< orphan*/  zo; } ;
typedef  TYPE_1__ Collator_object ;

/* Variables and functions */
 int /*<<< orphan*/  collator_object_destroy (TYPE_1__*) ; 
 TYPE_1__* php_intl_collator_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void Collator_objects_free(zend_object *object )
{
	Collator_object* co = php_intl_collator_fetch_object(object);

	zend_object_std_dtor(&co->zo );

	collator_object_destroy(co );
}