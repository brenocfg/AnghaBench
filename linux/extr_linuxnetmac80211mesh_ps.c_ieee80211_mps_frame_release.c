#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_2__* mesh; int /*<<< orphan*/ * tx_filtered; int /*<<< orphan*/ * ps_tx_buf; TYPE_1__ sta; int /*<<< orphan*/  sdata; } ;
struct ieee802_11_elems {int /*<<< orphan*/ * awake_window; int /*<<< orphan*/  tim_len; int /*<<< orphan*/  tim; } ;
struct TYPE_4__ {scalar_t__ plink_state; int /*<<< orphan*/  aid; } ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 scalar_t__ NL80211_PLINK_ESTAB ; 
 int /*<<< orphan*/  WLAN_STA_MPSP_OWNER ; 
 int /*<<< orphan*/  WLAN_STA_PS_STA ; 
 int ieee80211_check_tim (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_frame_deliver (struct sta_info*,int) ; 
 int /*<<< orphan*/  mpsp_trigger_send (struct sta_info*,int,int) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

void ieee80211_mps_frame_release(struct sta_info *sta,
				 struct ieee802_11_elems *elems)
{
	int ac, buffer_local = 0;
	bool has_buffered = false;

	if (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		has_buffered = ieee80211_check_tim(elems->tim, elems->tim_len,
						   sta->mesh->aid);

	if (has_buffered)
		mps_dbg(sta->sdata, "%pM indicates buffered frames\n",
			sta->sta.addr);

	/* only transmit to PS STA with announced, non-zero awake window */
	if (test_sta_flag(sta, WLAN_STA_PS_STA) &&
	    (!elems->awake_window || !le16_to_cpu(*elems->awake_window)))
		return;

	if (!test_sta_flag(sta, WLAN_STA_MPSP_OWNER))
		for (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			buffer_local += skb_queue_len(&sta->ps_tx_buf[ac]) +
					skb_queue_len(&sta->tx_filtered[ac]);

	if (!has_buffered && !buffer_local)
		return;

	if (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		mpsp_trigger_send(sta, has_buffered, !buffer_local);
	else
		mps_frame_deliver(sta, 1);
}