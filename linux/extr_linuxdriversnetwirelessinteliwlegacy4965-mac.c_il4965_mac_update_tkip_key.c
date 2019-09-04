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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct il_priv {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int dummy; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*) ; 
 int /*<<< orphan*/  il4965_update_tkip_key (struct il_priv*,struct ieee80211_key_conf*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
il4965_mac_update_tkip_key(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			   struct ieee80211_key_conf *keyconf,
			   struct ieee80211_sta *sta, u32 iv32, u16 * phase1key)
{
	struct il_priv *il = hw->priv;

	D_MAC80211("enter\n");

	il4965_update_tkip_key(il, keyconf, sta, iv32, phase1key);

	D_MAC80211("leave\n");
}