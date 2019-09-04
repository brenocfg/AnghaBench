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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  cpuset_hotplug_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpuset_track_online_nodes(struct notifier_block *self,
				unsigned long action, void *arg)
{
	schedule_work(&cpuset_hotplug_work);
	return NOTIFY_OK;
}