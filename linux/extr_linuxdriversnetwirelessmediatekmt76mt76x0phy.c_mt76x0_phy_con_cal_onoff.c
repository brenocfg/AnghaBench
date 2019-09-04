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
struct mt76x0_dev {int /*<<< orphan*/  con_mon_lock; int /*<<< orphan*/  bcn_freq_off; scalar_t__ avg_rssi; int /*<<< orphan*/  ap_bssid; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_FREQ_OFFSET_INVALID ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt76x0_phy_con_cal_onoff(struct mt76x0_dev *dev,
			       struct ieee80211_bss_conf *info)
{
	/* Start/stop collecting beacon data */
	spin_lock_bh(&dev->con_mon_lock);
	ether_addr_copy(dev->ap_bssid, info->bssid);
	dev->avg_rssi = 0;
	dev->bcn_freq_off = MT_FREQ_OFFSET_INVALID;
	spin_unlock_bh(&dev->con_mon_lock);
}