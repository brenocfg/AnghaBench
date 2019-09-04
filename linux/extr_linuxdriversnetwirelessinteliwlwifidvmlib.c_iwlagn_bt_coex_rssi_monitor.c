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
struct iwl_priv {scalar_t__ bt_traffic_load; scalar_t__ bt_is_sco; } ;

/* Variables and functions */
 scalar_t__ IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS ; 
 int /*<<< orphan*/  iwlagn_bt_adjust_rssi_monitor (struct iwl_priv*,int) ; 

void iwlagn_bt_coex_rssi_monitor(struct iwl_priv *priv)
{
	if (priv->bt_is_sco &&
	    priv->bt_traffic_load == IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS)
		iwlagn_bt_adjust_rssi_monitor(priv, true);
	else
		iwlagn_bt_adjust_rssi_monitor(priv, false);
}