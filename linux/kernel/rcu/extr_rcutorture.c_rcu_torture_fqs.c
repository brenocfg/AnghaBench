#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* fqs ) () ;} ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ ULONG_CMP_LT (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 TYPE_1__* cur_ops ; 
 int fqs_duration ; 
 scalar_t__ fqs_holdoff ; 
 unsigned long fqs_stutter ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stutter_wait (char*) ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 int /*<<< orphan*/  torture_must_stop () ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static int
rcu_torture_fqs(void *arg)
{
	unsigned long fqs_resume_time;
	int fqs_burst_remaining;

	VERBOSE_TOROUT_STRING("rcu_torture_fqs task started");
	do {
		fqs_resume_time = jiffies + fqs_stutter * HZ;
		while (ULONG_CMP_LT(jiffies, fqs_resume_time) &&
		       !kthread_should_stop()) {
			schedule_timeout_interruptible(1);
		}
		fqs_burst_remaining = fqs_duration;
		while (fqs_burst_remaining > 0 &&
		       !kthread_should_stop()) {
			cur_ops->fqs();
			udelay(fqs_holdoff);
			fqs_burst_remaining -= fqs_holdoff;
		}
		stutter_wait("rcu_torture_fqs");
	} while (!torture_must_stop());
	torture_kthread_stopping("rcu_torture_fqs");
	return 0;
}