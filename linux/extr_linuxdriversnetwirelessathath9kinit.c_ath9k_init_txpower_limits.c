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
struct ath_softc {struct ath_hw* sc_ah; } ;
struct TYPE_2__ {int hw_caps; } ;
struct ath_hw {struct ath9k_channel* curchan; TYPE_1__ caps; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_2GHZ ; 
 int ATH9K_HW_CAP_5GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  ath9k_init_band_txpower (struct ath_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_init_txpower_limits(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath9k_channel *curchan = ah->curchan;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		ath9k_init_band_txpower(sc, NL80211_BAND_2GHZ);
	if (ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		ath9k_init_band_txpower(sc, NL80211_BAND_5GHZ);

	ah->curchan = curchan;
}