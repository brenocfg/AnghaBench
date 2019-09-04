#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  ce; } ;
typedef  TYPE_3__ zend_object ;
struct TYPE_12__ {int /*<<< orphan*/  abbr; int /*<<< orphan*/  dst; int /*<<< orphan*/  utc_offset; } ;
struct TYPE_13__ {TYPE_1__ z; int /*<<< orphan*/  utc_offset; int /*<<< orphan*/  tz; } ;
struct TYPE_15__ {int initialized; int type; TYPE_3__ std; TYPE_2__ tzi; } ;
typedef  TYPE_4__ php_timezone_obj ;

/* Variables and functions */
#define  TIMELIB_ZONETYPE_ABBR 130 
#define  TIMELIB_ZONETYPE_ID 129 
#define  TIMELIB_ZONETYPE_OFFSET 128 
 TYPE_3__* date_object_new_timezone (int /*<<< orphan*/ ) ; 
 TYPE_4__* php_timezone_obj_from_obj (TYPE_3__*) ; 
 int /*<<< orphan*/  timelib_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_objects_clone_members (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static zend_object *date_object_clone_timezone(zend_object *this_ptr) /* {{{ */
{
	php_timezone_obj *old_obj = php_timezone_obj_from_obj(this_ptr);
	php_timezone_obj *new_obj = php_timezone_obj_from_obj(date_object_new_timezone(old_obj->std.ce));

	zend_objects_clone_members(&new_obj->std, &old_obj->std);
	if (!old_obj->initialized) {
		return &new_obj->std;
	}

	new_obj->type = old_obj->type;
	new_obj->initialized = 1;
	switch (new_obj->type) {
		case TIMELIB_ZONETYPE_ID:
			new_obj->tzi.tz = old_obj->tzi.tz;
			break;
		case TIMELIB_ZONETYPE_OFFSET:
			new_obj->tzi.utc_offset = old_obj->tzi.utc_offset;
			break;
		case TIMELIB_ZONETYPE_ABBR:
			new_obj->tzi.z.utc_offset = old_obj->tzi.z.utc_offset;
			new_obj->tzi.z.dst        = old_obj->tzi.z.dst;
			new_obj->tzi.z.abbr       = timelib_strdup(old_obj->tzi.z.abbr);
			break;
	}

	return &new_obj->std;
}