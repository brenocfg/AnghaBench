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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int clamping ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int pkg_cstate_ratio_cur ; 
 int pkg_state_counter () ; 
 int /*<<< orphan*/  poll_pkg_cstate_work ; 
 int rdtsc () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_pkg_cstate(struct work_struct *dummy)
{
	static u64 msr_last;
	static u64 tsc_last;

	u64 msr_now;
	u64 tsc_now;
	u64 val64;

	msr_now = pkg_state_counter();
	tsc_now = rdtsc();

	/* calculate pkg cstate vs tsc ratio */
	if (!msr_last || !tsc_last)
		pkg_cstate_ratio_cur = 1;
	else {
		if (tsc_now - tsc_last) {
			val64 = 100 * (msr_now - msr_last);
			do_div(val64, (tsc_now - tsc_last));
			pkg_cstate_ratio_cur = val64;
		}
	}

	/* update record */
	msr_last = msr_now;
	tsc_last = tsc_now;

	if (true == clamping)
		schedule_delayed_work(&poll_pkg_cstate_work, HZ);
}