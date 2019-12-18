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
typedef  int u8 ;
struct TYPE_2__ {int uapsd_queues; } ;
struct sta_info {TYPE_1__ sta; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_FRAME_RELEASE_PSPOLL ; 
 int /*<<< orphan*/  IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  ieee80211_sta_ps_deliver_response (struct sta_info*,int,int,int /*<<< orphan*/ ) ; 

void ieee80211_sta_ps_deliver_poll_response(struct sta_info *sta)
{
	u8 ignore_for_response = sta->sta.uapsd_queues;

	/*
	 * If all ACs are delivery-enabled then we should reply
	 * from any of them, if only some are enabled we reply
	 * only from the non-enabled ones.
	 */
	if (ignore_for_response == BIT(IEEE80211_NUM_ACS) - 1)
		ignore_for_response = 0;

	ieee80211_sta_ps_deliver_response(sta, 1, ignore_for_response,
					  IEEE80211_FRAME_RELEASE_PSPOLL);
}