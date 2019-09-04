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
struct ath_common {int dummy; } ;
struct ath_beacon_config {int dummy; } ;
struct ath9k_htc_priv {TYPE_1__* ah; struct ath_beacon_config cur_beacon_conf; } ;
struct TYPE_2__ {int opmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  ath9k_htc_beacon_config_adhoc (struct ath9k_htc_priv*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath9k_htc_beacon_config_ap (struct ath9k_htc_priv*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath9k_htc_beacon_config_sta (struct ath9k_htc_priv*,struct ath_beacon_config*) ; 
 struct ath_common* ath9k_hw_common (TYPE_1__*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

void ath9k_htc_beacon_reconfig(struct ath9k_htc_priv *priv)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath_beacon_config *cur_conf = &priv->cur_beacon_conf;

	switch (priv->ah->opmode) {
	case NL80211_IFTYPE_STATION:
		ath9k_htc_beacon_config_sta(priv, cur_conf);
		break;
	case NL80211_IFTYPE_ADHOC:
		ath9k_htc_beacon_config_adhoc(priv, cur_conf);
		break;
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_AP:
		ath9k_htc_beacon_config_ap(priv, cur_conf);
		break;
	default:
		ath_dbg(common, CONFIG, "Unsupported beaconing mode\n");
		return;
	}
}