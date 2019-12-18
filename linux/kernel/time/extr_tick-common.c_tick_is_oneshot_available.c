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
struct clock_event_device {int features; } ;
struct TYPE_2__ {int /*<<< orphan*/  evtdev; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_C3STOP ; 
 int CLOCK_EVT_FEAT_ONESHOT ; 
 struct clock_event_device* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int tick_broadcast_oneshot_available () ; 
 TYPE_1__ tick_cpu_device ; 

int tick_is_oneshot_available(void)
{
	struct clock_event_device *dev = __this_cpu_read(tick_cpu_device.evtdev);

	if (!dev || !(dev->features & CLOCK_EVT_FEAT_ONESHOT))
		return 0;
	if (!(dev->features & CLOCK_EVT_FEAT_C3STOP))
		return 1;
	return tick_broadcast_oneshot_available();
}