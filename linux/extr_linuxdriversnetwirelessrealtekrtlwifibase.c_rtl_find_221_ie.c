#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct octet_string {int length; int* octet; } ;
struct TYPE_3__ {scalar_t__ variable; } ;
struct TYPE_4__ {TYPE_1__ beacon; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ rtl_chk_vendor_ouisub (struct ieee80211_hw*,struct octet_string) ; 

__attribute__((used)) static bool rtl_find_221_ie(struct ieee80211_hw *hw, u8 *data,
		unsigned int len)
{
	struct ieee80211_mgmt *mgmt = (void *)data;
	struct octet_string vendor_ie;
	u8 *pos, *end;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = data + len;
	while (pos < end) {
		if (pos[0] == 221) {
			vendor_ie.length = pos[1];
			vendor_ie.octet = &pos[2];
			if (rtl_chk_vendor_ouisub(hw, vendor_ie))
				return true;
		}

		if (pos + 2 + pos[1] > end)
			return false;

		pos += 2 + pos[1];
	}
	return false;
}