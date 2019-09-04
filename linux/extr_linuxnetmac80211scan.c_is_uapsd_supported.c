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
struct ieee802_11_elems {int* wmm_info; int wmm_info_len; int* wmm_param; int wmm_param_len; } ;

/* Variables and functions */
 int IEEE80211_WMM_IE_AP_QOSINFO_UAPSD ; 

__attribute__((used)) static bool is_uapsd_supported(struct ieee802_11_elems *elems)
{
	u8 qos_info;

	if (elems->wmm_info && elems->wmm_info_len == 7
	    && elems->wmm_info[5] == 1)
		qos_info = elems->wmm_info[6];
	else if (elems->wmm_param && elems->wmm_param_len == 24
		 && elems->wmm_param[5] == 1)
		qos_info = elems->wmm_param[6];
	else
		/* no valid wmm information or parameter element found */
		return false;

	return qos_info & IEEE80211_WMM_IE_AP_QOSINFO_UAPSD;
}