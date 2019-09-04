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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct ath_hw {size_t* totalAdcIOddPhase; size_t* totalAdcIEvenPhase; size_t* totalAdcQOddPhase; size_t* totalAdcQEvenPhase; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_NEW_ADC_DC_GAIN_CORR (size_t) ; 
 size_t AR_PHY_NEW_ADC_GAIN_CORR_ENABLE ; 
 int /*<<< orphan*/  CALIBRATE ; 
 size_t REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,size_t) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t,...) ; 

__attribute__((used)) static void ar9002_hw_adc_gaincal_calibrate(struct ath_hw *ah, u8 numChains)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 iOddMeasOffset, iEvenMeasOffset, qOddMeasOffset, qEvenMeasOffset;
	u32 qGainMismatch, iGainMismatch, val, i;

	for (i = 0; i < numChains; i++) {
		iOddMeasOffset = ah->totalAdcIOddPhase[i];
		iEvenMeasOffset = ah->totalAdcIEvenPhase[i];
		qOddMeasOffset = ah->totalAdcQOddPhase[i];
		qEvenMeasOffset = ah->totalAdcQEvenPhase[i];

		ath_dbg(common, CALIBRATE,
			"Starting ADC Gain Cal for Chain %d\n", i);

		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_i = 0x%08x\n",
			i, iOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_i = 0x%08x\n",
			i, iEvenMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_q = 0x%08x\n",
			i, qOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_q = 0x%08x\n",
			i, qEvenMeasOffset);

		if (iOddMeasOffset != 0 && qEvenMeasOffset != 0) {
			iGainMismatch =
				((iEvenMeasOffset * 32) /
				 iOddMeasOffset) & 0x3f;
			qGainMismatch =
				((qOddMeasOffset * 32) /
				 qEvenMeasOffset) & 0x3f;

			ath_dbg(common, CALIBRATE,
				"Chn %d gain_mismatch_i = 0x%08x\n",
				i, iGainMismatch);
			ath_dbg(common, CALIBRATE,
				"Chn %d gain_mismatch_q = 0x%08x\n",
				i, qGainMismatch);

			val = REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i));
			val &= 0xfffff000;
			val |= (qGainMismatch) | (iGainMismatch << 6);
			REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i), val);

			ath_dbg(common, CALIBRATE,
				"ADC Gain Cal done for Chain %d\n", i);
		}
	}

	REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0),
		  REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0)) |
		  AR_PHY_NEW_ADC_GAIN_CORR_ENABLE);
}