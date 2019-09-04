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
struct TYPE_3__ {char* filename; } ;
typedef  TYPE_1__ ze_zip_object ;

/* Variables and functions */

__attribute__((used)) static char * php_zipobj_get_filename(ze_zip_object *obj) /* {{{ */
{

	if (!obj) {
		return NULL;
	}

	if (obj->filename) {
		return obj->filename;
	}
	return NULL;
}