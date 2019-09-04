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
struct TYPE_3__ {size_t length; unsigned char* buffer; size_t allocsz; scalar_t__ pos; } ;
typedef  TYPE_1__ mbfl_memory_device ;

/* Variables and functions */
 size_t MBFL_MEMORY_DEVICE_ALLOC_SIZE ; 
 scalar_t__ mbfl_malloc (size_t) ; 

void
mbfl_memory_device_init(mbfl_memory_device *device, size_t initsz, size_t allocsz)
{
	if (device) {
		device->length = 0;
		device->buffer = NULL;
		if (initsz > 0) {
			device->buffer = (unsigned char *)mbfl_malloc(initsz);
			if (device->buffer != NULL) {
				device->length = initsz;
			}
		}
		device->pos = 0;
		if (allocsz > MBFL_MEMORY_DEVICE_ALLOC_SIZE) {
			device->allocsz = allocsz;
		} else {
			device->allocsz = MBFL_MEMORY_DEVICE_ALLOC_SIZE;
		}
	}
}