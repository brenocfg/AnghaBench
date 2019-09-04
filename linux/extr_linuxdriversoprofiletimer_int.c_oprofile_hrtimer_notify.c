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
struct hrtimer {int dummy; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_RESTART ; 
 int /*<<< orphan*/  TICK_NSEC ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  hrtimer_forward_now (struct hrtimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oprofile_add_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum hrtimer_restart oprofile_hrtimer_notify(struct hrtimer *hrtimer)
{
	oprofile_add_sample(get_irq_regs(), 0);
	hrtimer_forward_now(hrtimer, ns_to_ktime(TICK_NSEC));
	return HRTIMER_RESTART;
}