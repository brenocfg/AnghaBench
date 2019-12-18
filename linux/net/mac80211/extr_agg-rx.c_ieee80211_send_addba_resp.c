#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_22__ {scalar_t__ has_he; } ;
struct TYPE_12__ {TYPE_9__ he_cap; } ;
struct sta_info {TYPE_10__ sta; struct ieee80211_sub_if_data* sdata; } ;
struct sk_buff {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_14__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_17__ {TYPE_3__ ibss; TYPE_1__ mgd; } ;
struct TYPE_15__ {scalar_t__ type; int /*<<< orphan*/ * addr; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__ vif; struct ieee80211_local* local; } ;
struct TYPE_18__ {void* status; void* timeout; void* capab; int /*<<< orphan*/  dialog_token; int /*<<< orphan*/  action_code; } ;
struct TYPE_19__ {TYPE_5__ addba_resp; } ;
struct TYPE_20__ {TYPE_6__ u; int /*<<< orphan*/  category; } ;
struct TYPE_21__ {TYPE_7__ action; } ;
struct ieee80211_mgmt {TYPE_8__ u; void* frame_control; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;
struct TYPE_13__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_11__ hw; } ;
struct ieee80211_addba_ext_ie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_ACTION ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SUPPORTS_AMSDU_IN_AMPDU ; 
 int /*<<< orphan*/  WLAN_ACTION_ADDBA_RESP ; 
 int /*<<< orphan*/  WLAN_CATEGORY_BACK ; 
 void* cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_add_addbaext (struct ieee80211_sub_if_data*,struct sk_buff*,struct ieee80211_addba_ext_ie const*) ; 
 int ieee80211_hw_check (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 struct ieee80211_mgmt* skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void ieee80211_send_addba_resp(struct sta_info *sta, u8 *da, u16 tid,
				      u8 dialog_token, u16 status, u16 policy,
				      u16 buf_size, u16 timeout,
				      const struct ieee80211_addba_ext_ie *addbaext)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;
	struct ieee80211_mgmt *mgmt;
	bool amsdu = ieee80211_hw_check(&local->hw, SUPPORTS_AMSDU_IN_AMPDU);
	u16 capab;

	skb = dev_alloc_skb(sizeof(*mgmt) +
		    2 + sizeof(struct ieee80211_addba_ext_ie) +
		    local->hw.extra_tx_headroom);
	if (!skb)
		return;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	mgmt = skb_put_zero(skb, 24);
	memcpy(mgmt->da, da, ETH_ALEN);
	memcpy(mgmt->sa, sdata->vif.addr, ETH_ALEN);
	if (sdata->vif.type == NL80211_IFTYPE_AP ||
	    sdata->vif.type == NL80211_IFTYPE_AP_VLAN ||
	    sdata->vif.type == NL80211_IFTYPE_MESH_POINT)
		memcpy(mgmt->bssid, sdata->vif.addr, ETH_ALEN);
	else if (sdata->vif.type == NL80211_IFTYPE_STATION)
		memcpy(mgmt->bssid, sdata->u.mgd.bssid, ETH_ALEN);
	else if (sdata->vif.type == NL80211_IFTYPE_ADHOC)
		memcpy(mgmt->bssid, sdata->u.ibss.bssid, ETH_ALEN);

	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	skb_put(skb, 1 + sizeof(mgmt->u.action.u.addba_resp));
	mgmt->u.action.category = WLAN_CATEGORY_BACK;
	mgmt->u.action.u.addba_resp.action_code = WLAN_ACTION_ADDBA_RESP;
	mgmt->u.action.u.addba_resp.dialog_token = dialog_token;

	capab = (u16)(amsdu << 0);	/* bit 0 A-MSDU support */
	capab |= (u16)(policy << 1);	/* bit 1 aggregation policy */
	capab |= (u16)(tid << 2); 	/* bit 5:2 TID number */
	capab |= (u16)(buf_size << 6);	/* bit 15:6 max size of aggregation */

	mgmt->u.action.u.addba_resp.capab = cpu_to_le16(capab);
	mgmt->u.action.u.addba_resp.timeout = cpu_to_le16(timeout);
	mgmt->u.action.u.addba_resp.status = cpu_to_le16(status);

	if (sta->sta.he_cap.has_he && addbaext)
		ieee80211_add_addbaext(sdata, skb, addbaext);

	ieee80211_tx_skb(sdata, skb);
}