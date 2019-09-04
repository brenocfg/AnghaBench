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
struct sta_info {int /*<<< orphan*/ * ps_tx_buf; int /*<<< orphan*/ * tx_filtered; } ;
typedef  enum ieee80211_frame_release_type { ____Placeholder_ieee80211_frame_release_type } ieee80211_frame_release_type ;

/* Variables and functions */
 int IEEE80211_FRAME_RELEASE_PSPOLL ; 
 int IEEE80211_NUM_ACS ; 
 int hweight16 (unsigned long) ; 
 int* ieee80211_ac_to_qos_mask ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ieee80211_sta_ps_more_data(struct sta_info *sta, u8 ignored_acs,
			   enum ieee80211_frame_release_type reason,
			   unsigned long driver_release_tids)
{
	int ac;

	/* If the driver has data on more than one TID then
	 * certainly there's more data if we release just a
	 * single frame now (from a single TID). This will
	 * only happen for PS-Poll.
	 */
	if (reason == IEEE80211_FRAME_RELEASE_PSPOLL &&
	    hweight16(driver_release_tids) > 1)
		return true;

	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		if (ignored_acs & ieee80211_ac_to_qos_mask[ac])
			continue;

		if (!skb_queue_empty(&sta->tx_filtered[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac]))
			return true;
	}

	return false;
}