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
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ TICKDEV_MODE_ONESHOT ; 
 int cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 TYPE_1__ tick_broadcast_device ; 
 int /*<<< orphan*/  tick_broadcast_mask ; 

bool tick_resume_check_broadcast(void)
{
	if (tick_broadcast_device.mode == TICKDEV_MODE_ONESHOT)
		return false;
	else
		return cpumask_test_cpu(smp_processor_id(), tick_broadcast_mask);
}