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
struct TYPE_2__ {int /*<<< orphan*/  cap_has_phyerr_counters; } ;
struct ath5k_hw {TYPE_1__ ah_capabilities; } ;
struct ath5k_ani_state {unsigned int ofdm_errors; unsigned int sum_ofdm_errors; unsigned int cck_errors; unsigned int sum_cck_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_PHYERR_CNT1 ; 
 int /*<<< orphan*/  AR5K_PHYERR_CNT2 ; 
 unsigned int ATH5K_ANI_CCK_TRIG_HIGH ; 
 unsigned int ATH5K_ANI_OFDM_TRIG_HIGH ; 
 unsigned int ATH5K_PHYERR_CNT_MAX ; 
 unsigned int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath5k_ani_save_and_clear_phy_errors(struct ath5k_hw *ah,
				    struct ath5k_ani_state *as)
{
	unsigned int ofdm_err, cck_err;

	if (!ah->ah_capabilities.cap_has_phyerr_counters)
		return 0;

	ofdm_err = ath5k_hw_reg_read(ah, AR5K_PHYERR_CNT1);
	cck_err = ath5k_hw_reg_read(ah, AR5K_PHYERR_CNT2);

	/* reset counters first, we might be in a hurry (interrupt) */
	ath5k_hw_reg_write(ah, ATH5K_PHYERR_CNT_MAX - ATH5K_ANI_OFDM_TRIG_HIGH,
			   AR5K_PHYERR_CNT1);
	ath5k_hw_reg_write(ah, ATH5K_PHYERR_CNT_MAX - ATH5K_ANI_CCK_TRIG_HIGH,
			   AR5K_PHYERR_CNT2);

	ofdm_err = ATH5K_ANI_OFDM_TRIG_HIGH - (ATH5K_PHYERR_CNT_MAX - ofdm_err);
	cck_err = ATH5K_ANI_CCK_TRIG_HIGH - (ATH5K_PHYERR_CNT_MAX - cck_err);

	/* sometimes both can be zero, especially when there is a superfluous
	 * second interrupt. detect that here and return an error. */
	if (ofdm_err <= 0 && cck_err <= 0)
		return 0;

	/* avoid negative values should one of the registers overflow */
	if (ofdm_err > 0) {
		as->ofdm_errors += ofdm_err;
		as->sum_ofdm_errors += ofdm_err;
	}
	if (cck_err > 0) {
		as->cck_errors += cck_err;
		as->sum_cck_errors += cck_err;
	}
	return 1;
}