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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  const* addr; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; struct ieee80211_local* local; } ;
struct ieee80211_msrment_ie {int /*<<< orphan*/  type; int /*<<< orphan*/  token; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; int /*<<< orphan*/  mode; int /*<<< orphan*/  token; } ;
struct TYPE_10__ {int length; TYPE_7__ msr_elem; int /*<<< orphan*/  element_id; int /*<<< orphan*/  dialog_token; int /*<<< orphan*/  action_code; } ;
struct TYPE_11__ {TYPE_3__ measurement; } ;
struct TYPE_12__ {TYPE_4__ u; int /*<<< orphan*/  category; } ;
struct TYPE_13__ {TYPE_5__ action; } ;
struct ieee80211_mgmt {TYPE_6__ u; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;
struct TYPE_8__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 int /*<<< orphan*/  IEEE80211_SPCT_MSR_RPRT_MODE_REFUSED ; 
 int IEEE80211_STYPE_ACTION ; 
 int /*<<< orphan*/  WLAN_ACTION_SPCT_MSR_RPRT ; 
 int /*<<< orphan*/  WLAN_CATEGORY_SPECTRUM_MGMT ; 
 int /*<<< orphan*/  WLAN_EID_MEASURE_REPORT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 struct ieee80211_mgmt* skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void ieee80211_send_refuse_measurement_request(struct ieee80211_sub_if_data *sdata,
					struct ieee80211_msrment_ie *request_ie,
					const u8 *da, const u8 *bssid,
					u8 dialog_token)
{
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;
	struct ieee80211_mgmt *msr_report;

	skb = dev_alloc_skb(sizeof(*msr_report) + local->hw.extra_tx_headroom +
				sizeof(struct ieee80211_msrment_ie));
	if (!skb)
		return;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	msr_report = skb_put_zero(skb, 24);
	memcpy(msr_report->da, da, ETH_ALEN);
	memcpy(msr_report->sa, sdata->vif.addr, ETH_ALEN);
	memcpy(msr_report->bssid, bssid, ETH_ALEN);
	msr_report->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						IEEE80211_STYPE_ACTION);

	skb_put(skb, 1 + sizeof(msr_report->u.action.u.measurement));
	msr_report->u.action.category = WLAN_CATEGORY_SPECTRUM_MGMT;
	msr_report->u.action.u.measurement.action_code =
				WLAN_ACTION_SPCT_MSR_RPRT;
	msr_report->u.action.u.measurement.dialog_token = dialog_token;

	msr_report->u.action.u.measurement.element_id = WLAN_EID_MEASURE_REPORT;
	msr_report->u.action.u.measurement.length =
			sizeof(struct ieee80211_msrment_ie);

	memset(&msr_report->u.action.u.measurement.msr_elem, 0,
		sizeof(struct ieee80211_msrment_ie));
	msr_report->u.action.u.measurement.msr_elem.token = request_ie->token;
	msr_report->u.action.u.measurement.msr_elem.mode |=
			IEEE80211_SPCT_MSR_RPRT_MODE_REFUSED;
	msr_report->u.action.u.measurement.msr_elem.type = request_ie->type;

	ieee80211_tx_skb(sdata, skb);
}