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
struct il_priv {int /*<<< orphan*/  scan_check; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; TYPE_1__* ops; int /*<<< orphan*/  scan_start; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_2__ {int (* request_scan ) (struct il_priv*,struct ieee80211_vif*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*) ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  IL_SCAN_CHECK_WATCHDOG ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  S_SCAN_ABORTING ; 
 int /*<<< orphan*/  S_SCAN_HW ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct il_priv*,struct ieee80211_vif*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il_scan_initiate(struct il_priv *il, struct ieee80211_vif *vif)
{
	int ret;

	lockdep_assert_held(&il->mutex);

	cancel_delayed_work(&il->scan_check);

	if (!il_is_ready_rf(il)) {
		IL_WARN("Request scan called when driver not ready.\n");
		return -EIO;
	}

	if (test_bit(S_SCAN_HW, &il->status)) {
		D_SCAN("Multiple concurrent scan requests in parallel.\n");
		return -EBUSY;
	}

	if (test_bit(S_SCAN_ABORTING, &il->status)) {
		D_SCAN("Scan request while abort pending.\n");
		return -EBUSY;
	}

	D_SCAN("Starting scan...\n");

	set_bit(S_SCANNING, &il->status);
	il->scan_start = jiffies;

	ret = il->ops->request_scan(il, vif);
	if (ret) {
		clear_bit(S_SCANNING, &il->status);
		return ret;
	}

	queue_delayed_work(il->workqueue, &il->scan_check,
			   IL_SCAN_CHECK_WATCHDOG);

	return 0;
}