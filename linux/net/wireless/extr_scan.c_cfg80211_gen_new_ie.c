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
typedef  int u8 ;
struct element {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int const WLAN_EID_EXTENSION ; 
 int /*<<< orphan*/  WLAN_EID_EXT_NON_INHERITANCE ; 
 int const WLAN_EID_NON_TX_BSSID_CAP ; 
 int const WLAN_EID_SSID ; 
 int const WLAN_EID_VENDOR_SPECIFIC ; 
 struct element* cfg80211_find_ext_elem (int /*<<< orphan*/ ,int*,size_t) ; 
 scalar_t__ cfg80211_find_ext_ie (int const,int*,size_t) ; 
 int* cfg80211_find_ie (int const,int const*,size_t) ; 
 scalar_t__ cfg80211_is_element_inherited (struct element const*,struct element const*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmemdup (int const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int const*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int const) ; 

__attribute__((used)) static size_t cfg80211_gen_new_ie(const u8 *ie, size_t ielen,
				  const u8 *subelement, size_t subie_len,
				  u8 *new_ie, gfp_t gfp)
{
	u8 *pos, *tmp;
	const u8 *tmp_old, *tmp_new;
	const struct element *non_inherit_elem;
	u8 *sub_copy;

	/* copy subelement as we need to change its content to
	 * mark an ie after it is processed.
	 */
	sub_copy = kmemdup(subelement, subie_len, gfp);
	if (!sub_copy)
		return 0;

	pos = &new_ie[0];

	/* set new ssid */
	tmp_new = cfg80211_find_ie(WLAN_EID_SSID, sub_copy, subie_len);
	if (tmp_new) {
		memcpy(pos, tmp_new, tmp_new[1] + 2);
		pos += (tmp_new[1] + 2);
	}

	/* get non inheritance list if exists */
	non_inherit_elem =
		cfg80211_find_ext_elem(WLAN_EID_EXT_NON_INHERITANCE,
				       sub_copy, subie_len);

	/* go through IEs in ie (skip SSID) and subelement,
	 * merge them into new_ie
	 */
	tmp_old = cfg80211_find_ie(WLAN_EID_SSID, ie, ielen);
	tmp_old = (tmp_old) ? tmp_old + tmp_old[1] + 2 : ie;

	while (tmp_old + tmp_old[1] + 2 - ie <= ielen) {
		if (tmp_old[0] == 0) {
			tmp_old++;
			continue;
		}

		if (tmp_old[0] == WLAN_EID_EXTENSION)
			tmp = (u8 *)cfg80211_find_ext_ie(tmp_old[2], sub_copy,
							 subie_len);
		else
			tmp = (u8 *)cfg80211_find_ie(tmp_old[0], sub_copy,
						     subie_len);

		if (!tmp) {
			const struct element *old_elem = (void *)tmp_old;

			/* ie in old ie but not in subelement */
			if (cfg80211_is_element_inherited(old_elem,
							  non_inherit_elem)) {
				memcpy(pos, tmp_old, tmp_old[1] + 2);
				pos += tmp_old[1] + 2;
			}
		} else {
			/* ie in transmitting ie also in subelement,
			 * copy from subelement and flag the ie in subelement
			 * as copied (by setting eid field to WLAN_EID_SSID,
			 * which is skipped anyway).
			 * For vendor ie, compare OUI + type + subType to
			 * determine if they are the same ie.
			 */
			if (tmp_old[0] == WLAN_EID_VENDOR_SPECIFIC) {
				if (!memcmp(tmp_old + 2, tmp + 2, 5)) {
					/* same vendor ie, copy from
					 * subelement
					 */
					memcpy(pos, tmp, tmp[1] + 2);
					pos += tmp[1] + 2;
					tmp[0] = WLAN_EID_SSID;
				} else {
					memcpy(pos, tmp_old, tmp_old[1] + 2);
					pos += tmp_old[1] + 2;
				}
			} else {
				/* copy ie from subelement into new ie */
				memcpy(pos, tmp, tmp[1] + 2);
				pos += tmp[1] + 2;
				tmp[0] = WLAN_EID_SSID;
			}
		}

		if (tmp_old + tmp_old[1] + 2 - ie == ielen)
			break;

		tmp_old += tmp_old[1] + 2;
	}

	/* go through subelement again to check if there is any ie not
	 * copied to new ie, skip ssid, capability, bssid-index ie
	 */
	tmp_new = sub_copy;
	while (tmp_new + tmp_new[1] + 2 - sub_copy <= subie_len) {
		if (!(tmp_new[0] == WLAN_EID_NON_TX_BSSID_CAP ||
		      tmp_new[0] == WLAN_EID_SSID)) {
			memcpy(pos, tmp_new, tmp_new[1] + 2);
			pos += tmp_new[1] + 2;
		}
		if (tmp_new + tmp_new[1] + 2 - sub_copy == subie_len)
			break;
		tmp_new += tmp_new[1] + 2;
	}

	kfree(sub_copy);
	return pos - new_ie;
}