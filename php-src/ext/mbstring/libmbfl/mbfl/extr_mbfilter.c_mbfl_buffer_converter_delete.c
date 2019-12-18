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
struct TYPE_3__ {int /*<<< orphan*/  device; scalar_t__ filter2; scalar_t__ filter1; } ;
typedef  TYPE_1__ mbfl_buffer_converter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_convert_filter_delete (scalar_t__) ; 
 int /*<<< orphan*/  mbfl_free (void*) ; 
 int /*<<< orphan*/  mbfl_memory_device_clear (int /*<<< orphan*/ *) ; 

void
mbfl_buffer_converter_delete(mbfl_buffer_converter *convd)
{
	if (convd != NULL) {
		if (convd->filter1) {
			mbfl_convert_filter_delete(convd->filter1);
		}
		if (convd->filter2) {
			mbfl_convert_filter_delete(convd->filter2);
		}
		mbfl_memory_device_clear(&convd->device);
		mbfl_free((void*)convd);
	}
}