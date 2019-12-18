#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_8__ {scalar_t__ pos; scalar_t__ length; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ mbfl_memory_device ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_memory_device_output (char,TYPE_2__*) ; 

mbfl_string *
mbfl_memory_device_result(mbfl_memory_device *device, mbfl_string *result)
{
	if (device && result) {
		result->len = device->pos;
		mbfl_memory_device_output('\0', device);
		result->val = device->buffer;
		device->buffer = NULL;
		device->length = 0;
		device->pos= 0;
		if (result->val == NULL) {
			result->len = 0;
			result = NULL;
		}
	} else {
		result = NULL;
	}

	return result;
}