#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* device_leave_context ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  device; TYPE_1__ exports; int /*<<< orphan*/  ref; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 scalar_t__ gs_valid (char*) ; 
 int /*<<< orphan*/  os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* thread_graphics ; 

void gs_leave_context(void)
{
	if (gs_valid("gs_leave_context")) {
		if (!os_atomic_dec_long(&thread_graphics->ref)) {
			graphics_t *graphics = thread_graphics;

			graphics->exports.device_leave_context(
				graphics->device);
			pthread_mutex_unlock(&graphics->mutex);
			thread_graphics = NULL;
		}
	}
}