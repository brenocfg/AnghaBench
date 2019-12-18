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
struct timekeeper {scalar_t__ next_leap_ktime; int /*<<< orphan*/  offs_real; } ;

/* Variables and functions */
 scalar_t__ KTIME_MAX ; 
 scalar_t__ ktime_sub (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ntp_get_next_leap () ; 

__attribute__((used)) static inline void tk_update_leap_state(struct timekeeper *tk)
{
	tk->next_leap_ktime = ntp_get_next_leap();
	if (tk->next_leap_ktime != KTIME_MAX)
		/* Convert to monotonic time */
		tk->next_leap_ktime = ktime_sub(tk->next_leap_ktime, tk->offs_real);
}