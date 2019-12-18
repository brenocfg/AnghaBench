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
struct sched_gate_list {int /*<<< orphan*/  cycle_close_time; int /*<<< orphan*/  entries; } ;
struct sched_entry {int /*<<< orphan*/  close_time; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool should_restart_cycle(const struct sched_gate_list *oper,
				 const struct sched_entry *entry)
{
	if (list_is_last(&entry->list, &oper->entries))
		return true;

	if (ktime_compare(entry->close_time, oper->cycle_close_time) == 0)
		return true;

	return false;
}