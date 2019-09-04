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
struct ieee80211_vif {int /*<<< orphan*/  csa_active; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_csa_finish (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ieee80211_csa_is_complete (struct ieee80211_vif*) ; 

bool ath9k_csa_is_finished(struct ath_softc *sc, struct ieee80211_vif *vif)
{
	if (!vif || !vif->csa_active)
		return false;

	if (!ieee80211_csa_is_complete(vif))
		return false;

	ieee80211_csa_finish(vif);
	return true;
}