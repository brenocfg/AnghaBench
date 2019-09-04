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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ const WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  _wil_cfg80211_find_ie (scalar_t__ const*,scalar_t__,scalar_t__ const*,scalar_t__) ; 
 scalar_t__* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,scalar_t__) ; 

__attribute__((used)) static int _wil_cfg80211_merge_extra_ies(const u8 *ies1, u16 ies1_len,
					 const u8 *ies2, u16 ies2_len,
					 u8 **merged_ies, u16 *merged_len)
{
	u8 *buf, *dpos;
	const u8 *spos;

	if (!ies1)
		ies1_len = 0;

	if (!ies2)
		ies2_len = 0;

	if (ies1_len == 0 && ies2_len == 0) {
		*merged_ies = NULL;
		*merged_len = 0;
		return 0;
	}

	buf = kmalloc(ies1_len + ies2_len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	if (ies1)
		memcpy(buf, ies1, ies1_len);
	dpos = buf + ies1_len;
	spos = ies2;
	while (spos && (spos + 1 < ies2 + ies2_len)) {
		/* IE tag at offset 0, length at offset 1 */
		u16 ielen = 2 + spos[1];

		if (spos + ielen > ies2 + ies2_len)
			break;
		if (spos[0] == WLAN_EID_VENDOR_SPECIFIC &&
		    (!ies1 || !_wil_cfg80211_find_ie(ies1, ies1_len,
						     spos, ielen))) {
			memcpy(dpos, spos, ielen);
			dpos += ielen;
		}
		spos += ielen;
	}

	*merged_ies = buf;
	*merged_len = dpos - buf;
	return 0;
}