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
struct TYPE_3__ {scalar_t__ pos; scalar_t__ length; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ mbfl_wchar_device ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_free (int /*<<< orphan*/ *) ; 

void
mbfl_wchar_device_clear(mbfl_wchar_device *device)
{
	if (device) {
		if (device->buffer) {
			mbfl_free(device->buffer);
		}
		device->buffer = NULL;
		device->length = 0;
		device->pos = 0;
	}
}