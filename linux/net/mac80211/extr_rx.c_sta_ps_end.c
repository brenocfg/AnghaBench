#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  aid; int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_1__ sta; int /*<<< orphan*/  sdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STA_PS_DELIVER ; 
 int /*<<< orphan*/  WLAN_STA_PS_DRIVER ; 
 int /*<<< orphan*/  WLAN_STA_PS_STA ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_sta_ps_deliver_wakeup (struct sta_info*) ; 
 int /*<<< orphan*/  ps_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sta_ps_end(struct sta_info *sta)
{
	ps_dbg(sta->sdata, "STA %pM aid %d exits power save mode\n",
	       sta->sta.addr, sta->sta.aid);

	if (test_sta_flag(sta, WLAN_STA_PS_DRIVER)) {
		/*
		 * Clear the flag only if the other one is still set
		 * so that the TX path won't start TX'ing new frames
		 * directly ... In the case that the driver flag isn't
		 * set ieee80211_sta_ps_deliver_wakeup() will clear it.
		 */
		clear_sta_flag(sta, WLAN_STA_PS_STA);
		ps_dbg(sta->sdata, "STA %pM aid %d driver-ps-blocked\n",
		       sta->sta.addr, sta->sta.aid);
		return;
	}

	set_sta_flag(sta, WLAN_STA_PS_DELIVER);
	clear_sta_flag(sta, WLAN_STA_PS_STA);
	ieee80211_sta_ps_deliver_wakeup(sta);
}