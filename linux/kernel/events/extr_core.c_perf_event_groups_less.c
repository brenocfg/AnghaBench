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
struct perf_event {scalar_t__ cpu; scalar_t__ group_index; } ;

/* Variables and functions */

__attribute__((used)) static bool
perf_event_groups_less(struct perf_event *left, struct perf_event *right)
{
	if (left->cpu < right->cpu)
		return true;
	if (left->cpu > right->cpu)
		return false;

	if (left->group_index < right->group_index)
		return true;
	if (left->group_index > right->group_index)
		return false;

	return false;
}