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
struct delayed_work {int dummy; } ;

/* Variables and functions */
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_delay_ms ; 
 int /*<<< orphan*/  schedule_delayed_work_on (int,struct delayed_work*,unsigned long) ; 

__attribute__((used)) static void pkg_thermal_schedule_work(int cpu, struct delayed_work *work)
{
	unsigned long ms = msecs_to_jiffies(notify_delay_ms);

	schedule_delayed_work_on(cpu, work, ms);
}