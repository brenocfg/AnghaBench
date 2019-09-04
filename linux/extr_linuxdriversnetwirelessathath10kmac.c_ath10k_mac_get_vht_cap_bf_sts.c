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
struct ath10k {int vht_cap_info; } ;

/* Variables and functions */
 int IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK ; 
 int IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT ; 

__attribute__((used)) static int ath10k_mac_get_vht_cap_bf_sts(struct ath10k *ar)
{
	int nsts = ar->vht_cap_info;

	nsts &= IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK;
	nsts >>= IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT;

	/* If firmware does not deliver to host number of space-time
	 * streams supported, assume it support up to 4 BF STS and return
	 * the value for VHT CAP: nsts-1)
	 */
	if (nsts == 0)
		return 3;

	return nsts;
}