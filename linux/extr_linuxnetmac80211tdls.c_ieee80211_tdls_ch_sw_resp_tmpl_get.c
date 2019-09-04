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
typedef  int /*<<< orphan*/  const* u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  tdls_initiator; } ;
struct sta_info {TYPE_1__ sta; struct ieee80211_sub_if_data* sdata; } ;
struct sk_buff {int data; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_ch_switch_timing {int dummy; } ;
typedef  int /*<<< orphan*/  extra_ies ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  WLAN_TDLS_CHANNEL_SWITCH_RESPONSE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  iee80211_tdls_add_ch_switch_timing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_build_data_template (struct ieee80211_sub_if_data*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_tdls_build_mgmt_packet_data (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ieee80211_tdls_find_sw_timing_ie (struct sk_buff*) ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,...) ; 

__attribute__((used)) static struct sk_buff *
ieee80211_tdls_ch_sw_resp_tmpl_get(struct sta_info *sta,
				   u32 *ch_sw_tm_ie_offset)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct sk_buff *skb;
	u8 extra_ies[2 + sizeof(struct ieee80211_ch_switch_timing)];

	/* initial timing are always zero in the template */
	iee80211_tdls_add_ch_switch_timing(extra_ies, 0, 0);

	skb = ieee80211_tdls_build_mgmt_packet_data(sdata, sta->sta.addr,
					WLAN_TDLS_CHANNEL_SWITCH_RESPONSE,
					0, 0, !sta->sta.tdls_initiator,
					extra_ies, sizeof(extra_ies), 0, NULL);
	if (!skb)
		return NULL;

	skb = ieee80211_build_data_template(sdata, skb, 0);
	if (IS_ERR(skb)) {
		tdls_dbg(sdata,
			 "Failed building TDLS channel switch resp frame\n");
		return NULL;
	}

	if (ch_sw_tm_ie_offset) {
		const u8 *tm_ie = ieee80211_tdls_find_sw_timing_ie(skb);

		if (!tm_ie) {
			tdls_dbg(sdata,
				 "No switch timing IE in TDLS switch resp\n");
			dev_kfree_skb_any(skb);
			return NULL;
		}

		*ch_sw_tm_ie_offset = tm_ie - skb->data;
	}

	tdls_dbg(sdata, "TDLS get channel switch response template for %pM\n",
		 sta->sta.addr);
	return skb;
}