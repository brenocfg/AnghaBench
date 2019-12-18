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
struct TYPE_3__ {int /*<<< orphan*/  std; int /*<<< orphan*/  interval; scalar_t__ end; scalar_t__ current; scalar_t__ start; } ;
typedef  TYPE_1__ php_period_obj ;

/* Variables and functions */
 TYPE_1__* php_period_obj_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timelib_rel_time_dtor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timelib_time_dtor (scalar_t__) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void date_object_free_storage_period(zend_object *object) /* {{{ */
{
	php_period_obj *intern = php_period_obj_from_obj(object);

	if (intern->start) {
		timelib_time_dtor(intern->start);
	}

	if (intern->current) {
		timelib_time_dtor(intern->current);
	}

	if (intern->end) {
		timelib_time_dtor(intern->end);
	}

	timelib_rel_time_dtor(intern->interval);
	zend_object_std_dtor(&intern->std);
}