#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* (* device_get_device_obj ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid (char*) ; 
 void* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* thread_graphics ; 

void *gs_get_device_obj(void)
{
	if (!gs_valid("gs_get_device_obj"))
		return NULL;

	return thread_graphics->exports.device_get_device_obj(
		thread_graphics->device);
}