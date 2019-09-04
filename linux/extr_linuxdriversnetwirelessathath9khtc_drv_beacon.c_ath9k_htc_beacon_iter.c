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
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ath9k_htc_vif {scalar_t__ beacon_configured; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 

__attribute__((used)) static void ath9k_htc_beacon_iter(void *data, u8 *mac, struct ieee80211_vif *vif)
{
	bool *beacon_configured = data;
	struct ath9k_htc_vif *avp = (struct ath9k_htc_vif *) vif->drv_priv;

	if (vif->type == NL80211_IFTYPE_STATION &&
	    avp->beacon_configured)
		*beacon_configured = true;
}