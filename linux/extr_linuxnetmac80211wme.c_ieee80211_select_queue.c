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
struct TYPE_14__ {int wme; } ;
struct sta_info {TYPE_7__ sta; } ;
struct sk_buff {int len; int priority; scalar_t__ protocol; int /*<<< orphan*/  const* data; } ;
struct mac80211_qos_map {int /*<<< orphan*/  qos_map; } ;
struct TYPE_12__ {int /*<<< orphan*/  const* bssid; } ;
struct TYPE_11__ {int /*<<< orphan*/  const* remote_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  sta; } ;
struct TYPE_13__ {TYPE_5__ mgd; TYPE_4__ wds; TYPE_3__ vlan; } ;
struct TYPE_9__ {int type; } ;
struct ieee80211_sub_if_data {scalar_t__ control_port_protocol; int /*<<< orphan*/  qos_map; TYPE_6__ u; TYPE_2__ vif; struct ieee80211_local* local; } ;
struct TYPE_8__ {scalar_t__ queues; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AC_BE ; 
 scalar_t__ IEEE80211_NUM_ACS ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_AP_VLAN 131 
#define  NL80211_IFTYPE_OCB 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int cfg80211_classify8021d (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_downgrade_queue (struct ieee80211_sub_if_data*,struct sta_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 

u16 ieee80211_select_queue(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb)
{
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta = NULL;
	const u8 *ra = NULL;
	bool qos = false;
	struct mac80211_qos_map *qos_map;
	u16 ret;

	if (local->hw.queues < IEEE80211_NUM_ACS || skb->len < 6) {
		skb->priority = 0; /* required for correct WPA/11i MIC */
		return 0;
	}

	rcu_read_lock();
	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP_VLAN:
		sta = rcu_dereference(sdata->u.vlan.sta);
		if (sta) {
			qos = sta->sta.wme;
			break;
		}
		/* fall through */
	case NL80211_IFTYPE_AP:
		ra = skb->data;
		break;
	case NL80211_IFTYPE_WDS:
		ra = sdata->u.wds.remote_addr;
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		qos = true;
		break;
#endif
	case NL80211_IFTYPE_STATION:
		/* might be a TDLS station */
		sta = sta_info_get(sdata, skb->data);
		if (sta)
			qos = sta->sta.wme;

		ra = sdata->u.mgd.bssid;
		break;
	case NL80211_IFTYPE_ADHOC:
		ra = skb->data;
		break;
	case NL80211_IFTYPE_OCB:
		/* all stations are required to support WME */
		qos = true;
		break;
	default:
		break;
	}

	if (!sta && ra && !is_multicast_ether_addr(ra)) {
		sta = sta_info_get(sdata, ra);
		if (sta)
			qos = sta->sta.wme;
	}

	if (!qos) {
		skb->priority = 0; /* required for correct WPA/11i MIC */
		ret = IEEE80211_AC_BE;
		goto out;
	}

	if (skb->protocol == sdata->control_port_protocol) {
		skb->priority = 7;
		goto downgrade;
	}

	/* use the data classifier to determine what 802.1d tag the
	 * data frame has */
	qos_map = rcu_dereference(sdata->qos_map);
	skb->priority = cfg80211_classify8021d(skb, qos_map ?
					       &qos_map->qos_map : NULL);

 downgrade:
	ret = ieee80211_downgrade_queue(sdata, sta, skb);
 out:
	rcu_read_unlock();
	return ret;
}