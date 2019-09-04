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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ ieee80211_vif_type_p2p (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_tof_iterator(void *_data, u8 *mac,
			     struct ieee80211_vif *vif)
{
	bool *enabled = _data;

	/* non bss vif exists */
	if (ieee80211_vif_type_p2p(vif) !=  NL80211_IFTYPE_STATION)
		*enabled = false;
}