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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct rtl_efuse {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_5__ {void* reason_code; void* params; int /*<<< orphan*/  action_code; } ;
struct TYPE_6__ {TYPE_1__ delba; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  category; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; void* frame_control; int /*<<< orphan*/  bssid; int /*<<< orphan*/  da; int /*<<< orphan*/  sa; } ;
struct ieee80211_hw {int /*<<< orphan*/  extra_tx_headroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_ACTION ; 
 int /*<<< orphan*/  WLAN_ACTION_DELBA ; 
 int /*<<< orphan*/  WLAN_CATEGORY_BACK ; 
 int WLAN_REASON_QSTA_TIMEOUT ; 
 void* cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 struct ieee80211_mgmt* skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

struct sk_buff *rtl_make_del_ba(struct ieee80211_hw *hw,
				u8 *sa, u8 *bssid, u16 tid)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct sk_buff *skb;
	struct ieee80211_mgmt *action_frame;
	u16 params;

	/* 27 = header + category + action + smps mode */
	skb = dev_alloc_skb(34 + hw->extra_tx_headroom);
	if (!skb)
		return NULL;

	skb_reserve(skb, hw->extra_tx_headroom);
	action_frame = skb_put_zero(skb, 34);
	memcpy(action_frame->sa, sa, ETH_ALEN);
	memcpy(action_frame->da, rtlefuse->dev_addr, ETH_ALEN);
	memcpy(action_frame->bssid, bssid, ETH_ALEN);
	action_frame->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_ACTION);
	action_frame->u.action.category = WLAN_CATEGORY_BACK;
	action_frame->u.action.u.delba.action_code = WLAN_ACTION_DELBA;
	params = (u16)(1 << 11);	/* bit 11 initiator */
	params |= (u16)(tid << 12);	/* bit 15:12 TID number */

	action_frame->u.action.u.delba.params = cpu_to_le16(params);
	action_frame->u.action.u.delba.reason_code =
		cpu_to_le16(WLAN_REASON_QSTA_TIMEOUT);

	return skb;
}