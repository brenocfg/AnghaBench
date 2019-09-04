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
struct TYPE_3__ {size_t length; size_t pos; unsigned char* buffer; } ;
typedef  TYPE_1__ mbfl_memory_device ;

/* Variables and functions */
 size_t MBFL_MEMORY_DEVICE_ALLOC_SIZE ; 
 size_t SIZE_MAX ; 
 scalar_t__ mbfl_realloc (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 

int
mbfl_memory_device_strncat(mbfl_memory_device *device, const char *psrc, size_t len)
{
	unsigned char *w;

	if (len > device->length - device->pos) {
		/* reallocate buffer */
		size_t newlen;
		unsigned char *tmp;

		if (len > SIZE_MAX - MBFL_MEMORY_DEVICE_ALLOC_SIZE
				|| device->length > SIZE_MAX - (len + MBFL_MEMORY_DEVICE_ALLOC_SIZE)) {
			/* overflow */
			return -1;
		}

		newlen = device->length + len + MBFL_MEMORY_DEVICE_ALLOC_SIZE;
		tmp = (unsigned char *)mbfl_realloc((void *)device->buffer, newlen);
		if (tmp == NULL) {
			return -1;
		}

		device->length = newlen;
		device->buffer = tmp;
	}

	w = &device->buffer[device->pos];
	memcpy(w, psrc, len);
	device->pos += len;

	return 0;
}