#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  const* data; scalar_t__ priority; } ;
struct TYPE_13__ {int /*<<< orphan*/  const* bssid; } ;
struct TYPE_12__ {int /*<<< orphan*/  const* remote_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  sta; } ;
struct TYPE_14__ {TYPE_6__ mgd; TYPE_5__ wds; TYPE_4__ vlan; } ;
struct TYPE_10__ {int type; } ;
struct ieee80211_sub_if_data {TYPE_7__ u; TYPE_3__ vif; struct ieee80211_local* local; } ;
struct TYPE_9__ {scalar_t__ queues; } ;
struct ieee80211_local {TYPE_2__ hw; TYPE_1__* ops; } ;
struct TYPE_8__ {scalar_t__ wake_tx_queue; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_NUM_ACS ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_AP_VLAN 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int /*<<< orphan*/  __ieee80211_select_queue (struct ieee80211_sub_if_data*,struct sta_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 struct sta_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 

u16 ieee80211_select_queue(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb)
{
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta = NULL;
	const u8 *ra = NULL;
	u16 ret;

	/* when using iTXQ, we can do this later */
	if (local->ops->wake_tx_queue)
		return 0;

	if (local->hw.queues < IEEE80211_NUM_ACS || skb->len < 6) {
		skb->priority = 0; /* required for correct WPA/11i MIC */
		return 0;
	}

	rcu_read_lock();
	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP_VLAN:
		sta = rcu_dereference(sdata->u.vlan.sta);
		if (sta)
			break;
		/* fall through */
	case NL80211_IFTYPE_AP:
		ra = skb->data;
		break;
	case NL80211_IFTYPE_WDS:
		ra = sdata->u.wds.remote_addr;
		break;
	case NL80211_IFTYPE_STATION:
		/* might be a TDLS station */
		sta = sta_info_get(sdata, skb->data);
		if (sta)
			break;

		ra = sdata->u.mgd.bssid;
		break;
	case NL80211_IFTYPE_ADHOC:
		ra = skb->data;
		break;
	default:
		break;
	}

	if (!sta && ra && !is_multicast_ether_addr(ra))
		sta = sta_info_get(sdata, ra);

	ret = __ieee80211_select_queue(sdata, sta, skb);

	rcu_read_unlock();
	return ret;
}