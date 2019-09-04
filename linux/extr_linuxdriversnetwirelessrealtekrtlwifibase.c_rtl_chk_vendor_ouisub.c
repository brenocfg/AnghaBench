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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  vendor; } ;
struct rtl_priv {TYPE_1__ mac80211; } ;
struct octet_string {int /*<<< orphan*/  octet; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEER_ATH ; 
 int /*<<< orphan*/  PEER_BROAD ; 
 int /*<<< orphan*/  PEER_CISCO ; 
 int /*<<< orphan*/  PEER_MARV ; 
 int /*<<< orphan*/  PEER_RAL ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool rtl_chk_vendor_ouisub(struct ieee80211_hw *hw,
				  struct octet_string vendor_ie)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	bool matched = false;
	static u8 athcap_1[] = { 0x00, 0x03, 0x7F };
	static u8 athcap_2[] = { 0x00, 0x13, 0x74 };
	static u8 broadcap_1[] = { 0x00, 0x10, 0x18 };
	static u8 broadcap_2[] = { 0x00, 0x0a, 0xf7 };
	static u8 broadcap_3[] = { 0x00, 0x05, 0xb5 };
	static u8 racap[] = { 0x00, 0x0c, 0x43 };
	static u8 ciscocap[] = { 0x00, 0x40, 0x96 };
	static u8 marvcap[] = { 0x00, 0x50, 0x43 };

	if (memcmp(vendor_ie.octet, athcap_1, 3) == 0 ||
		memcmp(vendor_ie.octet, athcap_2, 3) == 0) {
		rtlpriv->mac80211.vendor = PEER_ATH;
		matched = true;
	} else if (memcmp(vendor_ie.octet, broadcap_1, 3) == 0 ||
		memcmp(vendor_ie.octet, broadcap_2, 3) == 0 ||
		memcmp(vendor_ie.octet, broadcap_3, 3) == 0) {
		rtlpriv->mac80211.vendor = PEER_BROAD;
		matched = true;
	} else if (memcmp(vendor_ie.octet, racap, 3) == 0) {
		rtlpriv->mac80211.vendor = PEER_RAL;
		matched = true;
	} else if (memcmp(vendor_ie.octet, ciscocap, 3) == 0) {
		rtlpriv->mac80211.vendor = PEER_CISCO;
		matched = true;
	} else if (memcmp(vendor_ie.octet, marvcap, 3) == 0) {
		rtlpriv->mac80211.vendor = PEER_MARV;
		matched = true;
	}

	return matched;
}