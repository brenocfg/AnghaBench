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
struct TYPE_2__ {int /*<<< orphan*/  barrier; } ;
struct ath10k {TYPE_1__ wmi; int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_WMI_BARRIER_ECHO_ID ; 
 int /*<<< orphan*/  ATH10K_WMI_BARRIER_TIMEOUT_HZ ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_echo (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ath10k_wmi_barrier(struct ath10k *ar)
{
	int ret;
	int time_left;

	spin_lock_bh(&ar->data_lock);
	reinit_completion(&ar->wmi.barrier);
	spin_unlock_bh(&ar->data_lock);

	ret = ath10k_wmi_echo(ar, ATH10K_WMI_BARRIER_ECHO_ID);
	if (ret) {
		ath10k_warn(ar, "failed to submit wmi echo: %d\n", ret);
		return ret;
	}

	time_left = wait_for_completion_timeout(&ar->wmi.barrier,
						ATH10K_WMI_BARRIER_TIMEOUT_HZ);
	if (!time_left)
		return -ETIMEDOUT;

	return 0;
}