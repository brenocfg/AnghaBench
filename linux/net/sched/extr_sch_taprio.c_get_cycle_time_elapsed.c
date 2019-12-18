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
struct sched_gate_list {int /*<<< orphan*/  cycle_time; int /*<<< orphan*/  base_time; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  div_s64_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 get_cycle_time_elapsed(struct sched_gate_list *sched, ktime_t time)
{
	ktime_t time_since_sched_start;
	s32 time_elapsed;

	time_since_sched_start = ktime_sub(time, sched->base_time);
	div_s64_rem(time_since_sched_start, sched->cycle_time, &time_elapsed);

	return time_elapsed;
}