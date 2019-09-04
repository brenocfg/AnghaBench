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
struct TYPE_9__ {TYPE_1__ zo; } ;
typedef  TYPE_2__ Collator_object ;

/* Variables and functions */
 int /*<<< orphan*/  COLLATOR_ERROR_P (TYPE_2__*) ; 
 int /*<<< orphan*/  Collator_handlers ; 
 int /*<<< orphan*/  intl_error_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_object_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

zend_object *Collator_object_create(zend_class_entry *ce )
{
	Collator_object *intern = zend_object_alloc(sizeof(Collator_object), ce);
	intl_error_init(COLLATOR_ERROR_P(intern));
	zend_object_std_init(&intern->zo, ce );
	object_properties_init(&intern->zo, ce);

	intern->zo.handlers = &Collator_handlers;

	return &intern->zo;
}