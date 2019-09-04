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
struct TYPE_9__ {TYPE_1__ zend; int /*<<< orphan*/ * child; int /*<<< orphan*/ * me; } ;
typedef  TYPE_2__ ResourceBundle_object ;

/* Variables and functions */
 int /*<<< orphan*/  INTL_DATA_ERROR_P (TYPE_2__*) ; 
 int /*<<< orphan*/  ResourceBundle_object_handlers ; 
 int /*<<< orphan*/  intl_error_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_object_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *ResourceBundle_object_create( zend_class_entry *ce )
{
	ResourceBundle_object *rb;

	rb = zend_object_alloc(sizeof(ResourceBundle_object), ce);

	zend_object_std_init( &rb->zend, ce );
	object_properties_init( &rb->zend, ce);

	intl_error_init( INTL_DATA_ERROR_P(rb) );
	rb->me = NULL;
	rb->child = NULL;

	rb->zend.handlers = &ResourceBundle_object_handlers;

	return &rb->zend;
}