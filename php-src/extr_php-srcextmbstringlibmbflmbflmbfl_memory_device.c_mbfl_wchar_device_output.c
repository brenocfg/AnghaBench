#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pos; scalar_t__ length; int allocsz; unsigned int* buffer; } ;
typedef  TYPE_1__ mbfl_wchar_device ;

/* Variables and functions */
 int SIZE_MAX ; 
 scalar_t__ mbfl_realloc (void*,size_t) ; 

int
mbfl_wchar_device_output(int c, void *data)
{
	mbfl_wchar_device *device = (mbfl_wchar_device *)data;

	if (device->pos >= device->length) {
		/* reallocate buffer */
		size_t newlen;
		unsigned int *tmp;

		if (device->length > SIZE_MAX - device->allocsz) {
			/* overflow */
			return -1;
		}

		newlen = device->length + device->allocsz;
		if (newlen > SIZE_MAX / sizeof(int)) {
			/* overflow */
			return -1;
		}

		tmp = (unsigned int *)mbfl_realloc((void *)device->buffer, newlen*sizeof(int));
		if (tmp == NULL) {
			return -1;
		}
		device->length = newlen;
		device->buffer = tmp;
	}

	device->buffer[device->pos++] = c;

	return c;
}