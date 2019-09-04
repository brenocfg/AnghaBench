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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_credits_wq; } ;
struct ath10k {int /*<<< orphan*/  restart_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  dev_flags; TYPE_1__ wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_CRASH_FLUSH ; 
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int ESHUTDOWN ; 
 int HZ ; 
 scalar_t__ WMI_CMD_UNSUPPORTED ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,scalar_t__) ; 
 int ath10k_wmi_cmd_send_nowait (struct ath10k*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_wmi_tx_beacons_nowait (struct ath10k*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ath10k_wmi_cmd_send(struct ath10k *ar, struct sk_buff *skb, u32 cmd_id)
{
	int ret = -EOPNOTSUPP;

	might_sleep();

	if (cmd_id == WMI_CMD_UNSUPPORTED) {
		ath10k_warn(ar, "wmi command %d is not supported by firmware\n",
			    cmd_id);
		return ret;
	}

	wait_event_timeout(ar->wmi.tx_credits_wq, ({
		/* try to send pending beacons first. they take priority */
		ath10k_wmi_tx_beacons_nowait(ar);

		ret = ath10k_wmi_cmd_send_nowait(ar, skb, cmd_id);

		if (ret && test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags))
			ret = -ESHUTDOWN;

		(ret != -EAGAIN);
	}), 3 * HZ);

	if (ret)
		dev_kfree_skb_any(skb);

	if (ret == -EAGAIN) {
		ath10k_warn(ar, "wmi command %d timeout, restarting hardware\n",
			    cmd_id);
		queue_work(ar->workqueue, &ar->restart_work);
	}

	return ret;
}