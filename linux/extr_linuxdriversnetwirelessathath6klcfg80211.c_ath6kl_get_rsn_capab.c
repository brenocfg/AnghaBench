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
typedef  int u16 ;
struct cfg80211_beacon_data {int /*<<< orphan*/  tail_len; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 size_t* cfg80211_find_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_unaligned_le16 (size_t const*) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t const*,int) ; 

__attribute__((used)) static int ath6kl_get_rsn_capab(struct cfg80211_beacon_data *beacon,
				u8 *rsn_capab)
{
	const u8 *rsn_ie;
	size_t rsn_ie_len;
	u16 cnt;

	if (!beacon->tail)
		return -EINVAL;

	rsn_ie = cfg80211_find_ie(WLAN_EID_RSN, beacon->tail, beacon->tail_len);
	if (!rsn_ie)
		return -EINVAL;

	rsn_ie_len = *(rsn_ie + 1);
	/* skip element id and length */
	rsn_ie += 2;

	/* skip version */
	if (rsn_ie_len < 2)
		return -EINVAL;
	rsn_ie +=  2;
	rsn_ie_len -= 2;

	/* skip group cipher suite */
	if (rsn_ie_len < 4)
		return 0;
	rsn_ie +=  4;
	rsn_ie_len -= 4;

	/* skip pairwise cipher suite */
	if (rsn_ie_len < 2)
		return 0;
	cnt = get_unaligned_le16(rsn_ie);
	rsn_ie += (2 + cnt * 4);
	rsn_ie_len -= (2 + cnt * 4);

	/* skip akm suite */
	if (rsn_ie_len < 2)
		return 0;
	cnt = get_unaligned_le16(rsn_ie);
	rsn_ie += (2 + cnt * 4);
	rsn_ie_len -= (2 + cnt * 4);

	if (rsn_ie_len < 2)
		return 0;

	memcpy(rsn_capab, rsn_ie, 2);

	return 0;
}