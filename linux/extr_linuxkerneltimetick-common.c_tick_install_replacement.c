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
struct tick_device {int /*<<< orphan*/  evtdev; } ;
struct clock_event_device {int features; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_ONESHOT ; 
 int /*<<< orphan*/  clockevents_exchange_device (int /*<<< orphan*/ ,struct clock_event_device*) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int smp_processor_id () ; 
 struct tick_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_cpu_device ; 
 int /*<<< orphan*/  tick_oneshot_notify () ; 
 int /*<<< orphan*/  tick_setup_device (struct tick_device*,struct clock_event_device*,int,int /*<<< orphan*/ ) ; 

void tick_install_replacement(struct clock_event_device *newdev)
{
	struct tick_device *td = this_cpu_ptr(&tick_cpu_device);
	int cpu = smp_processor_id();

	clockevents_exchange_device(td->evtdev, newdev);
	tick_setup_device(td, newdev, cpu, cpumask_of(cpu));
	if (newdev->features & CLOCK_EVT_FEAT_ONESHOT)
		tick_oneshot_notify();
}