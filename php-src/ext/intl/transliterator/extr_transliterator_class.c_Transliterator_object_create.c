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
typedef  TYPE_2__ Transliterator_object ;

/* Variables and functions */
 int /*<<< orphan*/  Transliterator_handlers ; 
 int /*<<< orphan*/  object_properties_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transliterator_object_init (TYPE_2__*) ; 
 TYPE_2__* zend_object_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *Transliterator_object_create( zend_class_entry *ce )
{
	Transliterator_object* intern;

	intern = zend_object_alloc(sizeof(Transliterator_object), ce);

	zend_object_std_init( &intern->zo, ce );
    object_properties_init( &intern->zo, ce );
	transliterator_object_init( intern );

	intern->zo.handlers = &Transliterator_handlers;

	return &intern->zo;
}