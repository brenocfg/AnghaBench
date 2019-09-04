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
struct wmi_p2p_noa_info {int num_descriptors; int ctwindow_oppps; } ;
struct ieee80211_p2p_noa_desc {int dummy; } ;

/* Variables and functions */
 int WMI_P2P_OPPPS_ENABLE_BIT ; 

__attribute__((used)) static size_t ath10k_p2p_noa_ie_len_compute(const struct wmi_p2p_noa_info *noa)
{
	size_t len = 0;

	if (!noa->num_descriptors &&
	    !(noa->ctwindow_oppps & WMI_P2P_OPPPS_ENABLE_BIT))
		return 0;

	len += 1 + 1 + 4; /* EID + len + OUI */
	len += 1 + 2; /* noa attr + attr len */
	len += 1 + 1; /* index + oppps_ctwindow */
	len += noa->num_descriptors * sizeof(struct ieee80211_p2p_noa_desc);

	return len;
}