#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {scalar_t__ iterator; } ;
struct TYPE_6__ {TYPE_1__ inner; } ;
typedef  TYPE_2__ spl_dual_it_object ;

/* Variables and functions */
 int /*<<< orphan*/  spl_dual_it_free (TYPE_2__*) ; 
 TYPE_2__* spl_dual_it_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_iterator_dtor (scalar_t__) ; 
 int /*<<< orphan*/  zend_objects_destroy_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_dual_it_dtor(zend_object *_object)
{
	spl_dual_it_object *object = spl_dual_it_from_obj(_object);

	/* call standard dtor */
	zend_objects_destroy_object(_object);

	spl_dual_it_free(object);

	if (object->inner.iterator) {
		zend_iterator_dtor(object->inner.iterator);
	}
}