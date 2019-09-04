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
typedef  int u32 ;
struct ath_mci_profile {int aggr_limit; } ;
struct ath_btcoex {int btcoex_period; int duty_cycle; struct ath_mci_profile mci; } ;

/* Variables and functions */

__attribute__((used)) static void ath_mci_adjust_aggr_limit(struct ath_btcoex *btcoex)
{
	struct ath_mci_profile *mci = &btcoex->mci;
	u32 wlan_airtime = btcoex->btcoex_period *
				(100 - btcoex->duty_cycle) / 100;

	/*
	 * Scale: wlan_airtime is in ms, aggr_limit is in 0.25 ms.
	 * When wlan_airtime is less than 4ms, aggregation limit has to be
	 * adjusted half of wlan_airtime to ensure that the aggregation can fit
	 * without collision with BT traffic.
	 */
	if ((wlan_airtime <= 4) &&
	    (!mci->aggr_limit || (mci->aggr_limit > (2 * wlan_airtime))))
		mci->aggr_limit = 2 * wlan_airtime;
}