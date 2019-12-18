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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {scalar_t__ vht_supported; } ;
struct ieee80211_supported_band {TYPE_3__ vht_cap; } ;
struct ieee80211_if_managed {int /*<<< orphan*/  tdls_wider_bw_prohibited; } ;
struct TYPE_5__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; struct ieee80211_local* local; } ;
struct TYPE_8__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {TYPE_4__ hw; } ;
struct TYPE_6__ {int features; } ;

/* Variables and functions */
 int NL80211_FEATURE_TDLS_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  SUPPORTS_TDLS_BUFFER_STA ; 
 int /*<<< orphan*/  TDLS_WIDER_BW ; 
 int /*<<< orphan*/  WLAN_EID_EXT_CAPABILITY ; 
 int WLAN_EXT_CAPA4_TDLS_BUFFER_STA ; 
 int WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH ; 
 int /*<<< orphan*/  WLAN_EXT_CAPA5_TDLS_ENABLED ; 
 int /*<<< orphan*/  WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 
 int ieee80211_hw_check (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void ieee80211_tdls_add_ext_capab(struct ieee80211_sub_if_data *sdata,
					 struct sk_buff *skb)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	bool chan_switch = local->hw.wiphy->features &
			   NL80211_FEATURE_TDLS_CHANNEL_SWITCH;
	bool wider_band = ieee80211_hw_check(&local->hw, TDLS_WIDER_BW) &&
			  !ifmgd->tdls_wider_bw_prohibited;
	bool buffer_sta = ieee80211_hw_check(&local->hw,
					     SUPPORTS_TDLS_BUFFER_STA);
	struct ieee80211_supported_band *sband = ieee80211_get_sband(sdata);
	bool vht = sband && sband->vht_cap.vht_supported;
	u8 *pos = skb_put(skb, 10);

	*pos++ = WLAN_EID_EXT_CAPABILITY;
	*pos++ = 8; /* len */
	*pos++ = 0x0;
	*pos++ = 0x0;
	*pos++ = 0x0;
	*pos++ = (chan_switch ? WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH : 0) |
		 (buffer_sta ? WLAN_EXT_CAPA4_TDLS_BUFFER_STA : 0);
	*pos++ = WLAN_EXT_CAPA5_TDLS_ENABLED;
	*pos++ = 0;
	*pos++ = 0;
	*pos++ = (vht && wider_band) ? WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED : 0;
}