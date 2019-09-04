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
typedef  void* u8 ;
struct iwl_priv {void** scan_tx_ant; TYPE_1__* nvm_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  valid_tx_ant; } ;

/* Variables and functions */
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 void* fls (int /*<<< orphan*/ ) ; 

void iwl_init_scan_params(struct iwl_priv *priv)
{
	u8 ant_idx = fls(priv->nvm_data->valid_tx_ant) - 1;
	if (!priv->scan_tx_ant[NL80211_BAND_5GHZ])
		priv->scan_tx_ant[NL80211_BAND_5GHZ] = ant_idx;
	if (!priv->scan_tx_ant[NL80211_BAND_2GHZ])
		priv->scan_tx_ant[NL80211_BAND_2GHZ] = ant_idx;
}