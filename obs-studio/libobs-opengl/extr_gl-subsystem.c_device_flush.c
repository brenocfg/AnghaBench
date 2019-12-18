#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cur_swap; } ;
typedef  TYPE_1__ gs_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (TYPE_1__*) ; 
 int /*<<< orphan*/  glFlush () ; 

void device_flush(gs_device_t *device)
{
#ifdef __APPLE__
	if (!device->cur_swap)
		glFlush();
#else
	glFlush();
#endif

	UNUSED_PARAMETER(device);
}