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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  std; int /*<<< orphan*/  diff; } ;
typedef  TYPE_1__ php_interval_obj ;

/* Variables and functions */
 TYPE_1__* php_interval_obj_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timelib_rel_time_dtor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void date_object_free_storage_interval(zend_object *object) /* {{{ */
{
	php_interval_obj *intern = php_interval_obj_from_obj(object);

	timelib_rel_time_dtor(intern->diff);
	zend_object_std_dtor(&intern->std);
}