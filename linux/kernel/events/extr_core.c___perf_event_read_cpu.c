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
typedef  int /*<<< orphan*/  u16 ;
struct perf_event {int group_caps; } ;

/* Variables and functions */
 int PERF_EV_CAP_READ_ACTIVE_PKG ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  topology_physical_package_id (int) ; 

__attribute__((used)) static int __perf_event_read_cpu(struct perf_event *event, int event_cpu)
{
	u16 local_pkg, event_pkg;

	if (event->group_caps & PERF_EV_CAP_READ_ACTIVE_PKG) {
		int local_cpu = smp_processor_id();

		event_pkg = topology_physical_package_id(event_cpu);
		local_pkg = topology_physical_package_id(local_cpu);

		if (event_pkg == local_pkg)
			return local_cpu;
	}

	return event_cpu;
}