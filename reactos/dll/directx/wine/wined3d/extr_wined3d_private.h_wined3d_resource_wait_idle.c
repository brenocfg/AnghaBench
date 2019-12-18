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
struct wined3d_resource {int /*<<< orphan*/  access_count; TYPE_1__* device; } ;
struct wined3d_cs {scalar_t__ thread_id; int /*<<< orphan*/  thread; } ;
struct TYPE_2__ {struct wined3d_cs* cs; } ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 scalar_t__ InterlockedCompareExchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_pause () ; 

__attribute__((used)) static inline void wined3d_resource_wait_idle(struct wined3d_resource *resource)
{
    const struct wined3d_cs *cs = resource->device->cs;

    if (!cs->thread || cs->thread_id == GetCurrentThreadId())
        return;

    while (InterlockedCompareExchange(&resource->access_count, 0, 0))
        wined3d_pause();
}