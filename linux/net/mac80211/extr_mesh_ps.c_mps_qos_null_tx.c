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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct sta_info {int /*<<< orphan*/  sdata; TYPE_1__ sta; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_QOS_CTL_EOSP ; 
 int /*<<< orphan*/  WLAN_STA_PS_STA ; 
 int /*<<< orphan*/ * ieee80211_get_qos_ctl (void*) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mps_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* mps_qos_null_get (struct sta_info*) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mps_qos_null_tx(struct sta_info *sta)
{
	struct sk_buff *skb;

	skb = mps_qos_null_get(sta);
	if (!skb)
		return;

	mps_dbg(sta->sdata, "announcing peer-specific power mode to %pM\n",
		sta->sta.addr);

	/* don't unintentionally start a MPSP */
	if (!test_sta_flag(sta, WLAN_STA_PS_STA)) {
		u8 *qc = ieee80211_get_qos_ctl((void *) skb->data);

		qc[0] |= IEEE80211_QOS_CTL_EOSP;
	}

	ieee80211_tx_skb(sta->sdata, skb);
}