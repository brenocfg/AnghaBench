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
struct hrtimer_cpu_base {struct hrtimer_clock_base* clock_base; } ;
struct hrtimer_clock_base {int dummy; } ;

/* Variables and functions */
 unsigned int __ffs (unsigned int) ; 

__attribute__((used)) static struct hrtimer_clock_base *
__next_base(struct hrtimer_cpu_base *cpu_base, unsigned int *active)
{
	unsigned int idx;

	if (!*active)
		return NULL;

	idx = __ffs(*active);
	*active &= ~(1U << idx);

	return &cpu_base->clock_base[idx];
}