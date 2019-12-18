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
struct k_clock {int (* clock_adj ) (int /*<<< orphan*/  const,struct __kernel_timex*) ;} ;
struct __kernel_timex {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct k_clock* clockid_to_kclock (int /*<<< orphan*/  const) ; 
 int stub1 (int /*<<< orphan*/  const,struct __kernel_timex*) ; 

int do_clock_adjtime(const clockid_t which_clock, struct __kernel_timex * ktx)
{
	const struct k_clock *kc = clockid_to_kclock(which_clock);

	if (!kc)
		return -EINVAL;
	if (!kc->clock_adj)
		return -EOPNOTSUPP;

	return kc->clock_adj(which_clock, ktx);
}