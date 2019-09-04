#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {TYPE_2__* sc_ah; TYPE_1__* cur_chan; } ;
struct ath_common {int dummy; } ;
struct ath_beacon_config {int dummy; } ;
struct TYPE_5__ {int opmode; } ;
struct TYPE_4__ {struct ath_beacon_config beacon; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  ath9k_beacon_config_adhoc (struct ath_softc*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath9k_beacon_config_ap (struct ath_softc*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath9k_beacon_config_sta (TYPE_2__*,struct ath_beacon_config*) ; 
 struct ath_common* ath9k_hw_common (TYPE_2__*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

void ath9k_set_beacon(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_beacon_config *cur_conf = &sc->cur_chan->beacon;

	switch (sc->sc_ah->opmode) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_MESH_POINT:
		ath9k_beacon_config_ap(sc, cur_conf);
		break;
	case NL80211_IFTYPE_ADHOC:
		ath9k_beacon_config_adhoc(sc, cur_conf);
		break;
	case NL80211_IFTYPE_STATION:
		ath9k_beacon_config_sta(sc->sc_ah, cur_conf);
		break;
	default:
		ath_dbg(common, CONFIG, "Unsupported beaconing mode\n");
		return;
	}
}