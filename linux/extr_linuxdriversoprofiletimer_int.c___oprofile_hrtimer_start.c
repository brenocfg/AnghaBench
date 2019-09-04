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
struct hrtimer {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  TICK_NSEC ; 
 int /*<<< orphan*/  ctr_running ; 
 int /*<<< orphan*/  hrtimer_init (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oprofile_hrtimer ; 
 int /*<<< orphan*/  oprofile_hrtimer_notify ; 
 struct hrtimer* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __oprofile_hrtimer_start(void *unused)
{
	struct hrtimer *hrtimer = this_cpu_ptr(&oprofile_hrtimer);

	if (!ctr_running)
		return;

	hrtimer_init(hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrtimer->function = oprofile_hrtimer_notify;

	hrtimer_start(hrtimer, ns_to_ktime(TICK_NSEC),
		      HRTIMER_MODE_REL_PINNED);
}