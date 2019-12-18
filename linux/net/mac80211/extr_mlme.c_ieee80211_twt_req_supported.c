#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* mac_cap_info; } ;
struct TYPE_5__ {TYPE_1__ he_cap_elem; } ;
struct TYPE_6__ {TYPE_2__ he_cap; } ;
struct sta_info {TYPE_3__ sta; } ;
struct ieee802_11_elems {int ext_capab_len; int* ext_capab; } ;

/* Variables and functions */
 int IEEE80211_HE_MAC_CAP0_TWT_RES ; 
 int WLAN_EXT_CAPA10_TWT_RESPONDER_SUPPORT ; 

__attribute__((used)) static bool ieee80211_twt_req_supported(const struct sta_info *sta,
					const struct ieee802_11_elems *elems)
{
	if (elems->ext_capab_len < 10)
		return false;

	if (!(elems->ext_capab[9] & WLAN_EXT_CAPA10_TWT_RESPONDER_SUPPORT))
		return false;

	return sta->sta.he_cap.he_cap_elem.mac_cap_info[0] &
		IEEE80211_HE_MAC_CAP0_TWT_RES;
}