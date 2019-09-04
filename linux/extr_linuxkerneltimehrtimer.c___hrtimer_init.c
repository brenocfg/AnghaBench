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
struct hrtimer_cpu_base {int /*<<< orphan*/ * clock_base; } ;
struct hrtimer {int is_soft; int /*<<< orphan*/  node; int /*<<< orphan*/ * base; } ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;
typedef  scalar_t__ clockid_t ;

/* Variables and functions */
 scalar_t__ CLOCK_MONOTONIC ; 
 scalar_t__ CLOCK_REALTIME ; 
 int HRTIMER_MAX_CLOCK_BASES ; 
 int HRTIMER_MODE_REL ; 
 int HRTIMER_MODE_SOFT ; 
 int /*<<< orphan*/  hrtimer_bases ; 
 scalar_t__ hrtimer_clockid_to_base (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct hrtimer*,int /*<<< orphan*/ ,int) ; 
 struct hrtimer_cpu_base* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timerqueue_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __hrtimer_init(struct hrtimer *timer, clockid_t clock_id,
			   enum hrtimer_mode mode)
{
	bool softtimer = !!(mode & HRTIMER_MODE_SOFT);
	int base = softtimer ? HRTIMER_MAX_CLOCK_BASES / 2 : 0;
	struct hrtimer_cpu_base *cpu_base;

	memset(timer, 0, sizeof(struct hrtimer));

	cpu_base = raw_cpu_ptr(&hrtimer_bases);

	/*
	 * POSIX magic: Relative CLOCK_REALTIME timers are not affected by
	 * clock modifications, so they needs to become CLOCK_MONOTONIC to
	 * ensure POSIX compliance.
	 */
	if (clock_id == CLOCK_REALTIME && mode & HRTIMER_MODE_REL)
		clock_id = CLOCK_MONOTONIC;

	base += hrtimer_clockid_to_base(clock_id);
	timer->is_soft = softtimer;
	timer->base = &cpu_base->clock_base[base];
	timerqueue_init(&timer->node);
}