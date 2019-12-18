#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct ieee80211_mgd_assoc_data* assoc_data; } ;
struct TYPE_6__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; TYPE_2__ u; } ;
struct ieee80211_mgd_assoc_data {scalar_t__ tries; int timeout_started; scalar_t__ timeout; TYPE_4__* bss; } ;
struct TYPE_7__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_3__ hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ IEEE80211_ASSOC_MAX_TRIES ; 
 scalar_t__ IEEE80211_ASSOC_TIMEOUT ; 
 scalar_t__ IEEE80211_ASSOC_TIMEOUT_LONG ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  cfg80211_unlink_bss (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ieee80211_hw_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_assoc (struct ieee80211_sub_if_data*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ round_jiffies_up (scalar_t__) ; 
 int /*<<< orphan*/  run_again (struct ieee80211_sub_if_data*,scalar_t__) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int ieee80211_do_assoc(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_mgd_assoc_data *assoc_data = sdata->u.mgd.assoc_data;
	struct ieee80211_local *local = sdata->local;

	sdata_assert_lock(sdata);

	assoc_data->tries++;
	if (assoc_data->tries > IEEE80211_ASSOC_MAX_TRIES) {
		sdata_info(sdata, "association with %pM timed out\n",
			   assoc_data->bss->bssid);

		/*
		 * Most likely AP is not in the range so remove the
		 * bss struct for that AP.
		 */
		cfg80211_unlink_bss(local->hw.wiphy, assoc_data->bss);

		return -ETIMEDOUT;
	}

	sdata_info(sdata, "associate with %pM (try %d/%d)\n",
		   assoc_data->bss->bssid, assoc_data->tries,
		   IEEE80211_ASSOC_MAX_TRIES);
	ieee80211_send_assoc(sdata);

	if (!ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) {
		assoc_data->timeout = jiffies + IEEE80211_ASSOC_TIMEOUT;
		assoc_data->timeout_started = true;
		run_again(sdata, assoc_data->timeout);
	} else {
		assoc_data->timeout =
			round_jiffies_up(jiffies +
					 IEEE80211_ASSOC_TIMEOUT_LONG);
		assoc_data->timeout_started = true;
		run_again(sdata, assoc_data->timeout);
	}

	return 0;
}