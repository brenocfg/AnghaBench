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
struct TYPE_11__ {TYPE_1__ std; scalar_t__ diff; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_2__ php_interval_obj ;

/* Variables and functions */
 TYPE_1__* date_object_new_interval (int /*<<< orphan*/ ) ; 
 TYPE_2__* php_interval_obj_from_obj (TYPE_1__*) ; 
 scalar_t__ timelib_rel_time_clone (scalar_t__) ; 
 int /*<<< orphan*/  zend_objects_clone_members (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static zend_object *date_object_clone_interval(zend_object *this_ptr) /* {{{ */
{
	php_interval_obj *old_obj = php_interval_obj_from_obj(this_ptr);
	php_interval_obj *new_obj = php_interval_obj_from_obj(date_object_new_interval(old_obj->std.ce));

	zend_objects_clone_members(&new_obj->std, &old_obj->std);
	new_obj->initialized = old_obj->initialized;
	if (old_obj->diff) {
		new_obj->diff = timelib_rel_time_clone(old_obj->diff);
	}

	return &new_obj->std;
}