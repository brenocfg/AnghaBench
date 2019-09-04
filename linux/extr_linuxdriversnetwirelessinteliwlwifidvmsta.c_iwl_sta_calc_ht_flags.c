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
typedef  int u32 ;
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {int dummy; } ;
struct ieee80211_sta_ht_cap {scalar_t__ ampdu_density; scalar_t__ ampdu_factor; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {int smps_mode; int /*<<< orphan*/  addr; struct ieee80211_sta_ht_cap ht_cap; } ;
typedef  int __le32 ;

/* Variables and functions */
#define  IEEE80211_SMPS_DYNAMIC 130 
#define  IEEE80211_SMPS_OFF 129 
#define  IEEE80211_SMPS_STATIC 128 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_priv*,char*,int) ; 
 int STA_FLG_AGG_MPDU_DENSITY_MSK ; 
 int STA_FLG_AGG_MPDU_DENSITY_POS ; 
 int STA_FLG_HT40_EN_MSK ; 
 int STA_FLG_MAX_AGG_SIZE_MSK ; 
 int STA_FLG_MAX_AGG_SIZE_POS ; 
 int STA_FLG_MIMO_DIS_MSK ; 
 int STA_FLG_RTS_MIMO_PROT_MSK ; 
 int cpu_to_le32 (int) ; 
 scalar_t__ iwl_is_ht40_tx_allowed (struct iwl_priv*,struct iwl_rxon_context*,struct ieee80211_sta*) ; 

__attribute__((used)) static void iwl_sta_calc_ht_flags(struct iwl_priv *priv,
				  struct ieee80211_sta *sta,
				  struct iwl_rxon_context *ctx,
				  __le32 *flags, __le32 *mask)
{
	struct ieee80211_sta_ht_cap *sta_ht_inf = &sta->ht_cap;

	*mask = STA_FLG_RTS_MIMO_PROT_MSK |
		STA_FLG_MIMO_DIS_MSK |
		STA_FLG_HT40_EN_MSK |
		STA_FLG_MAX_AGG_SIZE_MSK |
		STA_FLG_AGG_MPDU_DENSITY_MSK;
	*flags = 0;

	if (!sta || !sta_ht_inf->ht_supported)
		return;

	IWL_DEBUG_INFO(priv, "STA %pM SM PS mode: %s\n",
			sta->addr,
			(sta->smps_mode == IEEE80211_SMPS_STATIC) ?
			"static" :
			(sta->smps_mode == IEEE80211_SMPS_DYNAMIC) ?
			"dynamic" : "disabled");

	switch (sta->smps_mode) {
	case IEEE80211_SMPS_STATIC:
		*flags |= STA_FLG_MIMO_DIS_MSK;
		break;
	case IEEE80211_SMPS_DYNAMIC:
		*flags |= STA_FLG_RTS_MIMO_PROT_MSK;
		break;
	case IEEE80211_SMPS_OFF:
		break;
	default:
		IWL_WARN(priv, "Invalid MIMO PS mode %d\n", sta->smps_mode);
		break;
	}

	*flags |= cpu_to_le32(
		(u32)sta_ht_inf->ampdu_factor << STA_FLG_MAX_AGG_SIZE_POS);

	*flags |= cpu_to_le32(
		(u32)sta_ht_inf->ampdu_density << STA_FLG_AGG_MPDU_DENSITY_POS);

	if (iwl_is_ht40_tx_allowed(priv, ctx, sta))
		*flags |= STA_FLG_HT40_EN_MSK;
}