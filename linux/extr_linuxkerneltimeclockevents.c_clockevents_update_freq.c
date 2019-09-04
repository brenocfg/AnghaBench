#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int __clockevents_update_freq (struct clock_event_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int tick_broadcast_update_freq (struct clock_event_device*,int /*<<< orphan*/ ) ; 

int clockevents_update_freq(struct clock_event_device *dev, u32 freq)
{
	unsigned long flags;
	int ret;

	local_irq_save(flags);
	ret = tick_broadcast_update_freq(dev, freq);
	if (ret == -ENODEV)
		ret = __clockevents_update_freq(dev, freq);
	local_irq_restore(flags);
	return ret;
}