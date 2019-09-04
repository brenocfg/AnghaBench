#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* device_enter_context ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  device; TYPE_1__ exports; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_leave_context () ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* thread_graphics ; 

void gs_enter_context(graphics_t *graphics)
{
	if (!ptr_valid(graphics, "gs_enter_context"))
		return;

	bool is_current = thread_graphics == graphics;
	if (thread_graphics && !is_current) {
		while (thread_graphics)
			gs_leave_context();
	}

	if (!is_current) {
		pthread_mutex_lock(&graphics->mutex);
		graphics->exports.device_enter_context(graphics->device);
		thread_graphics = graphics;
	}

	os_atomic_inc_long(&graphics->ref);
}