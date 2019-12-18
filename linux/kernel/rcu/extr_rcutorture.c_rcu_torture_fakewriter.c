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
struct TYPE_2__ {int /*<<< orphan*/  (* exp_sync ) () ;int /*<<< orphan*/  (* sync ) () ;int /*<<< orphan*/  (* cb_barrier ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_TORTURE_RANDOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_NICE ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ gp_exp ; 
 scalar_t__ gp_normal ; 
 int nfakewriters ; 
 int /*<<< orphan*/  rand ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  stutter_wait (char*) ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 int /*<<< orphan*/  torture_must_stop () ; 
 int torture_random (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
rcu_torture_fakewriter(void *arg)
{
	DEFINE_TORTURE_RANDOM(rand);

	VERBOSE_TOROUT_STRING("rcu_torture_fakewriter task started");
	set_user_nice(current, MAX_NICE);

	do {
		schedule_timeout_uninterruptible(1 + torture_random(&rand)%10);
		udelay(torture_random(&rand) & 0x3ff);
		if (cur_ops->cb_barrier != NULL &&
		    torture_random(&rand) % (nfakewriters * 8) == 0) {
			cur_ops->cb_barrier();
		} else if (gp_normal == gp_exp) {
			if (cur_ops->sync && torture_random(&rand) & 0x80)
				cur_ops->sync();
			else if (cur_ops->exp_sync)
				cur_ops->exp_sync();
		} else if (gp_normal && cur_ops->sync) {
			cur_ops->sync();
		} else if (cur_ops->exp_sync) {
			cur_ops->exp_sync();
		}
		stutter_wait("rcu_torture_fakewriter");
	} while (!torture_must_stop());

	torture_kthread_stopping("rcu_torture_fakewriter");
	return 0;
}