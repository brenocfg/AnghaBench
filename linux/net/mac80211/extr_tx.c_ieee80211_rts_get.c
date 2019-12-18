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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ieee80211_rts {int /*<<< orphan*/  ta; int /*<<< orphan*/  ra; int /*<<< orphan*/  duration; int /*<<< orphan*/  frame_control; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int IEEE80211_FTYPE_CTL ; 
 int IEEE80211_STYPE_RTS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ieee80211_rts_duration (struct ieee80211_hw*,struct ieee80211_vif*,size_t,struct ieee80211_tx_info const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ieee80211_rts_get(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		       const void *frame, size_t frame_len,
		       const struct ieee80211_tx_info *frame_txctl,
		       struct ieee80211_rts *rts)
{
	const struct ieee80211_hdr *hdr = frame;

	rts->frame_control =
	    cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_RTS);
	rts->duration = ieee80211_rts_duration(hw, vif, frame_len,
					       frame_txctl);
	memcpy(rts->ra, hdr->addr1, sizeof(rts->ra));
	memcpy(rts->ta, hdr->addr2, sizeof(rts->ta));
}