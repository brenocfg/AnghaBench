#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 scalar_t__ HARDWARE_TYPE_RTL8192SE ; 
 scalar_t__ HARDWARE_TYPE_RTL8822BE ; 
 size_t HIGH_QUEUE ; 
 size_t MGNT_QUEUE ; 
 size_t* ac_to_hwq ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 struct ieee80211_hdr* rtl_get_hdr (struct sk_buff*) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 _rtl_mac_to_hwqueue(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	__le16 fc = rtl_get_fc(skb);
	u8 queue_index = skb_get_queue_mapping(skb);
	struct ieee80211_hdr *hdr;

	if (unlikely(ieee80211_is_beacon(fc)))
		return BEACON_QUEUE;
	if (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		return MGNT_QUEUE;
	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE)
		if (ieee80211_is_nullfunc(fc))
			return HIGH_QUEUE;
	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8822BE) {
		hdr = rtl_get_hdr(skb);

		if (is_multicast_ether_addr(hdr->addr1) ||
		    is_broadcast_ether_addr(hdr->addr1))
			return HIGH_QUEUE;
	}

	return ac_to_hwq[queue_index];
}