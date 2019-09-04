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
struct sta_info {int flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PS2 ; 
 int IEEE80211_FTYPE_CTL ; 
 int IEEE80211_STYPE_PSPOLL ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int WLAN_STA_PS ; 
 int /*<<< orphan*/  schedule_packet_send (int /*<<< orphan*/ *,struct sta_info*) ; 

__attribute__((used)) static void hostap_update_sta_ps2(local_info_t *local, struct sta_info *sta,
				  int pwrmgt, int type, int stype)
{
	if (pwrmgt && !(sta->flags & WLAN_STA_PS)) {
		sta->flags |= WLAN_STA_PS;
		PDEBUG(DEBUG_PS2, "STA %pM changed to use PS "
		       "mode (type=0x%02X, stype=0x%02X)\n",
		       sta->addr, type >> 2, stype >> 4);
	} else if (!pwrmgt && (sta->flags & WLAN_STA_PS)) {
		sta->flags &= ~WLAN_STA_PS;
		PDEBUG(DEBUG_PS2, "STA %pM changed to not use "
		       "PS mode (type=0x%02X, stype=0x%02X)\n",
		       sta->addr, type >> 2, stype >> 4);
		if (type != IEEE80211_FTYPE_CTL ||
		    stype != IEEE80211_STYPE_PSPOLL)
			schedule_packet_send(local, sta);
	}
}