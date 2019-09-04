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
struct ath_softc {int rng_last; struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_TEST ; 
 int /*<<< orphan*/  AR_PHY_TEST_BBB_OBS_SEL ; 
 int /*<<< orphan*/  AR_PHY_TEST_CTL_RX_OBS_SEL ; 
 int /*<<< orphan*/  AR_PHY_TEST_CTL_STATUS ; 
 int /*<<< orphan*/  AR_PHY_TEST_RX_OBS_SEL_BIT5 ; 
 int /*<<< orphan*/  AR_PHY_TST_ADC ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 

__attribute__((used)) static int ath9k_rng_data_read(struct ath_softc *sc, u32 *buf, u32 buf_size)
{
	int i, j;
	u32  v1, v2, rng_last = sc->rng_last;
	struct ath_hw *ah = sc->sc_ah;

	ath9k_ps_wakeup(sc);

	REG_RMW_FIELD(ah, AR_PHY_TEST, AR_PHY_TEST_BBB_OBS_SEL, 1);
	REG_CLR_BIT(ah, AR_PHY_TEST, AR_PHY_TEST_RX_OBS_SEL_BIT5);
	REG_RMW_FIELD(ah, AR_PHY_TEST_CTL_STATUS, AR_PHY_TEST_CTL_RX_OBS_SEL, 0);

	for (i = 0, j = 0; i < buf_size; i++) {
		v1 = REG_READ(ah, AR_PHY_TST_ADC) & 0xffff;
		v2 = REG_READ(ah, AR_PHY_TST_ADC) & 0xffff;

		/* wait for data ready */
		if (v1 && v2 && rng_last != v1 && v1 != v2 && v1 != 0xffff &&
		    v2 != 0xffff)
			buf[j++] = (v1 << 16) | v2;

		rng_last = v2;
	}

	ath9k_ps_restore(sc);

	sc->rng_last = rng_last;

	return j << 2;
}