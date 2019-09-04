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
typedef  size_t u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int HW_OP_UNSUPPORTED ; 
 size_t PERF_COUNT_HW_MAX ; 

__attribute__((used)) static int
armpmu_map_hw_event(const unsigned (*event_map)[PERF_COUNT_HW_MAX], u64 config)
{
	int mapping;

	if (config >= PERF_COUNT_HW_MAX)
		return -EINVAL;

	if (!event_map)
		return -ENOENT;

	mapping = (*event_map)[config];
	return mapping == HW_OP_UNSUPPORTED ? -ENOENT : mapping;
}