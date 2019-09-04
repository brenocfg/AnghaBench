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
struct ath_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ath9k_enable_dynack(struct ath_softc *sc)
{
#ifdef CONFIG_ATH9K_DYNACK
	u32 rfilt;
	struct ath_hw *ah = sc->sc_ah;

	ath_dynack_reset(ah);

	ah->dynack.enabled = true;
	rfilt = ath_calcrxfilter(sc);
	ath9k_hw_setrxfilter(ah, rfilt);
#endif
}