#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_object ;
struct TYPE_11__ {TYPE_1__ std; int /*<<< orphan*/  num; } ;
typedef  TYPE_2__ gmp_object ;

/* Variables and functions */
 TYPE_2__* GET_GMP_OBJECT_FROM_OBJ (TYPE_1__*) ; 
 TYPE_1__* gmp_create_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_objects_clone_members (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static zend_object *gmp_clone_obj(zend_object *obj) /* {{{ */
{
	gmp_object *old_object = GET_GMP_OBJECT_FROM_OBJ(obj);
	gmp_object *new_object = GET_GMP_OBJECT_FROM_OBJ(gmp_create_object(obj->ce));

	zend_objects_clone_members( &new_object->std, &old_object->std);

	mpz_set(new_object->num, old_object->num);

	return &new_object->std;
}