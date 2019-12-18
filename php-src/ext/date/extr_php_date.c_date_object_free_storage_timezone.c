#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {int /*<<< orphan*/  abbr; } ;
struct TYPE_6__ {TYPE_1__ z; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  std; TYPE_2__ tzi; } ;
typedef  TYPE_3__ php_timezone_obj ;

/* Variables and functions */
 scalar_t__ TIMELIB_ZONETYPE_ABBR ; 
 TYPE_3__* php_timezone_obj_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timelib_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void date_object_free_storage_timezone(zend_object *object) /* {{{ */
{
	php_timezone_obj *intern = php_timezone_obj_from_obj(object);

	if (intern->type == TIMELIB_ZONETYPE_ABBR) {
		timelib_free(intern->tzi.z.abbr);
	}
	zend_object_std_dtor(&intern->std);
}