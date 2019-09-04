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

/* Variables and functions */
 int /*<<< orphan*/  __oprofile_hrtimer_stop (unsigned int) ; 

__attribute__((used)) static int oprofile_timer_prep_down(unsigned int cpu)
{
	__oprofile_hrtimer_stop(cpu);
	return 0;
}