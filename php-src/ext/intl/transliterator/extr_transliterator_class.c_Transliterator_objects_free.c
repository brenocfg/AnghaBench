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
typedef  TYPE_1__ Transliterator_object ;

/* Variables and functions */
 TYPE_1__* php_intl_transliterator_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transliterator_object_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Transliterator_objects_free( zend_object *object )
{
	Transliterator_object* to = php_intl_transliterator_fetch_object(object);

	zend_object_std_dtor( &to->zo );

	transliterator_object_destroy( to );
}