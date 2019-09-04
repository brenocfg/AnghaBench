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
typedef  int u64 ;
struct arch_timer_context {int cnt_ctl; } ;

/* Variables and functions */
 int ARCH_TIMER_CTRL_IT_STAT ; 
 int /*<<< orphan*/  kvm_timer_compute_delta (struct arch_timer_context*) ; 

__attribute__((used)) static u64 read_timer_ctl(struct arch_timer_context *timer)
{
	/*
	 * Set ISTATUS bit if it's expired.
	 * Note that according to ARMv8 ARM Issue A.k, ISTATUS bit is
	 * UNKNOWN when ENABLE bit is 0, so we chose to set ISTATUS bit
	 * regardless of ENABLE bit for our implementation convenience.
	 */
	if (!kvm_timer_compute_delta(timer))
		return timer->cnt_ctl | ARCH_TIMER_CTRL_IT_STAT;
	else
		return timer->cnt_ctl;
}