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
struct rtl_efuse {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  smps_control; int /*<<< orphan*/  action; } ;
struct TYPE_6__ {TYPE_1__ ht_smps; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  category; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;
struct ieee80211_hw {int /*<<< orphan*/  extra_tx_headroom; } ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
#define  IEEE80211_SMPS_AUTOMATIC 132 
#define  IEEE80211_SMPS_DYNAMIC 131 
#define  IEEE80211_SMPS_NUM_MODES 130 
#define  IEEE80211_SMPS_OFF 129 
#define  IEEE80211_SMPS_STATIC 128 
 int IEEE80211_STYPE_ACTION ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_CATEGORY_HT ; 
 int /*<<< orphan*/  WLAN_HT_ACTION_SMPS ; 
 int /*<<< orphan*/  WLAN_HT_SMPS_CONTROL_DISABLED ; 
 int /*<<< orphan*/  WLAN_HT_SMPS_CONTROL_DYNAMIC ; 
 int /*<<< orphan*/  WLAN_HT_SMPS_CONTROL_STATIC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 struct ieee80211_mgmt* skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *rtl_make_smps_action(struct ieee80211_hw *hw,
				     enum ieee80211_smps_mode smps,
				     u8 *da, u8 *bssid)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct sk_buff *skb;
	struct ieee80211_mgmt *action_frame;

	/* 27 = header + category + action + smps mode */
	skb = dev_alloc_skb(27 + hw->extra_tx_headroom);
	if (!skb)
		return NULL;

	skb_reserve(skb, hw->extra_tx_headroom);
	action_frame = skb_put_zero(skb, 27);
	memcpy(action_frame->da, da, ETH_ALEN);
	memcpy(action_frame->sa, rtlefuse->dev_addr, ETH_ALEN);
	memcpy(action_frame->bssid, bssid, ETH_ALEN);
	action_frame->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_ACTION);
	action_frame->u.action.category = WLAN_CATEGORY_HT;
	action_frame->u.action.u.ht_smps.action = WLAN_HT_ACTION_SMPS;
	switch (smps) {
	case IEEE80211_SMPS_AUTOMATIC:/* 0 */
	case IEEE80211_SMPS_NUM_MODES:/* 4 */
		WARN_ON(1);
	/* fall through */
	case IEEE80211_SMPS_OFF:/* 1 */ /*MIMO_PS_NOLIMIT*/
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DISABLED;/* 0 */
		break;
	case IEEE80211_SMPS_STATIC:/* 2 */ /*MIMO_PS_STATIC*/
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_STATIC;/* 1 */
		break;
	case IEEE80211_SMPS_DYNAMIC:/* 3 */ /*MIMO_PS_DYNAMIC*/
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DYNAMIC;/* 3 */
		break;
	}

	return skb;
}