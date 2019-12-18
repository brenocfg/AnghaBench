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
struct sched_gate_list {int /*<<< orphan*/  cycle_time_extension; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_base_time (struct sched_gate_list const*) ; 

__attribute__((used)) static bool should_change_schedules(const struct sched_gate_list *admin,
				    const struct sched_gate_list *oper,
				    ktime_t close_time)
{
	ktime_t next_base_time, extension_time;

	if (!admin)
		return false;

	next_base_time = sched_base_time(admin);

	/* This is the simple case, the close_time would fall after
	 * the next schedule base_time.
	 */
	if (ktime_compare(next_base_time, close_time) <= 0)
		return true;

	/* This is the cycle_time_extension case, if the close_time
	 * plus the amount that can be extended would fall after the
	 * next schedule base_time, we can extend the current schedule
	 * for that amount.
	 */
	extension_time = ktime_add_ns(close_time, oper->cycle_time_extension);

	/* FIXME: the IEEE 802.1Q-2018 Specification isn't clear about
	 * how precisely the extension should be made. So after
	 * conformance testing, this logic may change.
	 */
	if (ktime_compare(next_base_time, extension_time) <= 0)
		return true;

	return false;
}