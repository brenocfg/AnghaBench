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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  last_update; int /*<<< orphan*/  interval; int /*<<< orphan*/  period; } ;
struct zd_mac {scalar_t__ type; int associated; int /*<<< orphan*/  lock; int /*<<< orphan*/  short_preamble; int /*<<< orphan*/  chip; TYPE_1__ beacon; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  use_short_preamble; int /*<<< orphan*/  bssid; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  dtim_period; scalar_t__ enable_beacon; } ;

/* Variables and functions */
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 struct sk_buff* ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_rts_cts (struct zd_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_disable_hwint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_enable_hwint (int /*<<< orphan*/ *) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  zd_mac_config_beacon (struct ieee80211_hw*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  zd_mac_dev (struct zd_mac*) ; 
 int /*<<< orphan*/  zd_set_beacon_interval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void zd_op_bss_info_changed(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_bss_conf *bss_conf,
				   u32 changes)
{
	struct zd_mac *mac = zd_hw_mac(hw);
	int associated;

	dev_dbg_f(zd_mac_dev(mac), "changes: %x\n", changes);

	if (mac->type == NL80211_IFTYPE_MESH_POINT ||
	    mac->type == NL80211_IFTYPE_ADHOC ||
	    mac->type == NL80211_IFTYPE_AP) {
		associated = true;
		if (changes & BSS_CHANGED_BEACON) {
			struct sk_buff *beacon = ieee80211_beacon_get(hw, vif);

			if (beacon) {
				zd_chip_disable_hwint(&mac->chip);
				zd_mac_config_beacon(hw, beacon, false);
				zd_chip_enable_hwint(&mac->chip);
			}
		}

		if (changes & BSS_CHANGED_BEACON_ENABLED) {
			u16 interval = 0;
			u8 period = 0;

			if (bss_conf->enable_beacon) {
				period = bss_conf->dtim_period;
				interval = bss_conf->beacon_int;
			}

			spin_lock_irq(&mac->lock);
			mac->beacon.period = period;
			mac->beacon.interval = interval;
			mac->beacon.last_update = jiffies;
			spin_unlock_irq(&mac->lock);

			zd_set_beacon_interval(&mac->chip, interval, period,
					       mac->type);
		}
	} else
		associated = is_valid_ether_addr(bss_conf->bssid);

	spin_lock_irq(&mac->lock);
	mac->associated = associated;
	spin_unlock_irq(&mac->lock);

	/* TODO: do hardware bssid filtering */

	if (changes & BSS_CHANGED_ERP_PREAMBLE) {
		spin_lock_irq(&mac->lock);
		mac->short_preamble = bss_conf->use_short_preamble;
		spin_unlock_irq(&mac->lock);

		set_rts_cts(mac, bss_conf->use_short_preamble);
	}
}