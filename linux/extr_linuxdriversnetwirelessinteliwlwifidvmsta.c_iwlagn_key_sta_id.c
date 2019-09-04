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
struct iwl_vif_priv {TYPE_1__* ctx; } ;
struct iwl_priv {int dummy; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ap_sta_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_INVALID_STATION ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  iwl_sta_id (struct ieee80211_sta*) ; 

__attribute__((used)) static u8 iwlagn_key_sta_id(struct iwl_priv *priv,
			    struct ieee80211_vif *vif,
			    struct ieee80211_sta *sta)
{
	struct iwl_vif_priv *vif_priv = (void *)vif->drv_priv;

	if (sta)
		return iwl_sta_id(sta);

	/*
	 * The device expects GTKs for station interfaces to be
	 * installed as GTKs for the AP station. If we have no
	 * station ID, then use the ap_sta_id in that case.
	 */
	if (vif->type == NL80211_IFTYPE_STATION && vif_priv->ctx)
		return vif_priv->ctx->ap_sta_id;

	return IWL_INVALID_STATION;
}