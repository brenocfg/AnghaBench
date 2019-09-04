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
struct TYPE_2__ {int /*<<< orphan*/  is_40mhz; int /*<<< orphan*/  enabled; } ;
struct iwl_rxon_context {TYPE_1__ ht; } ;
struct iwl_priv {int dummy; } ;
struct ieee80211_sta {scalar_t__ bandwidth; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 

bool iwl_is_ht40_tx_allowed(struct iwl_priv *priv,
			    struct iwl_rxon_context *ctx,
			    struct ieee80211_sta *sta)
{
	if (!ctx->ht.enabled || !ctx->ht.is_40mhz)
		return false;

#ifdef CONFIG_IWLWIFI_DEBUGFS
	if (priv->disable_ht40)
		return false;
#endif

	/* special case for RXON */
	if (!sta)
		return true;

	return sta->bandwidth >= IEEE80211_STA_RX_BW_40;
}