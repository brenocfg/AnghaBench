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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_node {int /*<<< orphan*/  key_idx; struct ieee80211_vif* vif; struct ieee80211_sta* sta; struct ath_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_dynack_node_init (int /*<<< orphan*/ ,struct ath_node*) ; 
 int /*<<< orphan*/  ath_tx_node_init (struct ath_softc*,struct ath_node*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath_node_attach(struct ath_softc *sc, struct ieee80211_sta *sta,
			    struct ieee80211_vif *vif)
{
	struct ath_node *an;
	an = (struct ath_node *)sta->drv_priv;

	an->sc = sc;
	an->sta = sta;
	an->vif = vif;
	memset(&an->key_idx, 0, sizeof(an->key_idx));

	ath_tx_node_init(sc, an);

	ath_dynack_node_init(sc->sc_ah, an);
}