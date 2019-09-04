#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_6__ {TYPE_2__* data; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; TYPE_3__ tcm; } ;
struct TYPE_4__ {int rx_bytes; scalar_t__ detected; int /*<<< orphan*/  rate; } ;
struct TYPE_5__ {TYPE_1__ uapsd_nonagg_detect; scalar_t__ opened_rx_ba_sessions; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 unsigned long ewma_rate_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ iwl_mvm_has_new_rx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_uapsd_agg_disconnect_iter ; 

__attribute__((used)) static void iwl_mvm_check_uapsd_agg_expected_tpt(struct iwl_mvm *mvm,
						 unsigned int elapsed,
						 int mac)
{
	u64 bytes = mvm->tcm.data[mac].uapsd_nonagg_detect.rx_bytes;
	u64 tpt;
	unsigned long rate;

	rate = ewma_rate_read(&mvm->tcm.data[mac].uapsd_nonagg_detect.rate);

	if (!rate || mvm->tcm.data[mac].opened_rx_ba_sessions ||
	    mvm->tcm.data[mac].uapsd_nonagg_detect.detected)
		return;

	if (iwl_mvm_has_new_rx_api(mvm)) {
		tpt = 8 * bytes; /* kbps */
		do_div(tpt, elapsed);
		rate *= 1000; /* kbps */
		if (tpt < 22 * rate / 100)
			return;
	} else {
		/*
		 * the rate here is actually the threshold, in 100Kbps units,
		 * so do the needed conversion from bytes to 100Kbps:
		 * 100kb = bits / (100 * 1000),
		 * 100kbps = 100kb / (msecs / 1000) ==
		 *           (bits / (100 * 1000)) / (msecs / 1000) ==
		 *           bits / (100 * msecs)
		 */
		tpt = (8 * bytes);
		do_div(tpt, elapsed * 100);
		if (tpt < rate)
			return;
	}

	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_uapsd_agg_disconnect_iter, &mac);
}