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
struct perf_cpu_map {int dummy; } ;

/* Variables and functions */
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 

const struct perf_cpu_map *cpu_map__online(void) /* thread unsafe */
{
	static const struct perf_cpu_map *online = NULL;

	if (!online)
		online = perf_cpu_map__new(NULL); /* from /sys/devices/system/cpu/online */

	return online;
}