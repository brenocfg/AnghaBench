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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; scalar_t__ drv_priv; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  bssid; } ;
struct ath10k_vif {int /*<<< orphan*/  connection_loss_work; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_handle_beacon_iter(void *data, u8 *mac,
					  struct ieee80211_vif *vif)
{
	struct sk_buff *skb = data;
	struct ieee80211_mgmt *mgmt = (void *)skb->data;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;

	if (vif->type != NL80211_IFTYPE_STATION)
		return;

	if (!ether_addr_equal(mgmt->bssid, vif->bss_conf.bssid))
		return;

	cancel_delayed_work(&arvif->connection_loss_work);
}