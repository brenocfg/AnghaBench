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
struct rsi_hw {scalar_t__ sc_nvifs; struct ieee80211_vif** vifs; struct rsi_common* priv; } ;
struct rsi_common {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct ieee80211_hw {struct rsi_hw* priv; } ;
typedef  enum opmode { ____Placeholder_opmode } opmode ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 int /*<<< orphan*/  INFO_ZONE ; 
 int RSI_MAX_VIFS ; 
 int RSI_OPMODE_UNSUPPORTED ; 
 int /*<<< orphan*/  VAP_DELETE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int rsi_map_intf_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_set_vap_capabilities (struct rsi_common*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsi_mac80211_remove_interface(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;
	enum opmode opmode;
	int i;

	rsi_dbg(INFO_ZONE, "Remove Interface Called\n");

	mutex_lock(&common->mutex);

	if (adapter->sc_nvifs <= 0) {
		mutex_unlock(&common->mutex);
		return;
	}

	opmode = rsi_map_intf_mode(vif->type);
	if (opmode == RSI_OPMODE_UNSUPPORTED) {
		rsi_dbg(ERR_ZONE, "Opmode error : %d\n", opmode);
		mutex_unlock(&common->mutex);
		return;
	}
	for (i = 0; i < RSI_MAX_VIFS; i++) {
		if (!adapter->vifs[i])
			continue;
		if (vif == adapter->vifs[i]) {
			rsi_set_vap_capabilities(common, opmode, vif->addr,
						 i, VAP_DELETE);
			adapter->sc_nvifs--;
			adapter->vifs[i] = NULL;
		}
	}
	mutex_unlock(&common->mutex);
}