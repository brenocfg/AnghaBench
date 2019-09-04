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
typedef  int u8 ;
typedef  int u32 ;
struct ath_hw {int* totalPowerMeasI; int* totalPowerMeasQ; int* totalIqCorrMeas; } ;
struct ath_common {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4 (int) ; 
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4_IQCORR_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF ; 
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void ar9002_hw_iqcalibrate(struct ath_hw *ah, u8 numChains)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 powerMeasQ, powerMeasI, iqCorrMeas;
	u32 qCoffDenom, iCoffDenom;
	int32_t qCoff, iCoff;
	int iqCorrNeg, i;

	for (i = 0; i < numChains; i++) {
		powerMeasI = ah->totalPowerMeasI[i];
		powerMeasQ = ah->totalPowerMeasQ[i];
		iqCorrMeas = ah->totalIqCorrMeas[i];

		ath_dbg(common, CALIBRATE,
			"Starting IQ Cal and Correction for Chain %d\n",
			i);

		ath_dbg(common, CALIBRATE,
			"Original: Chn %d iq_corr_meas = 0x%08x\n",
			i, ah->totalIqCorrMeas[i]);

		iqCorrNeg = 0;

		if (iqCorrMeas > 0x80000000) {
			iqCorrMeas = (0xffffffff - iqCorrMeas) + 1;
			iqCorrNeg = 1;
		}

		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_i = 0x%08x\n",
			i, powerMeasI);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_q = 0x%08x\n",
			i, powerMeasQ);
		ath_dbg(common, CALIBRATE, "iqCorrNeg is 0x%08x\n", iqCorrNeg);

		iCoffDenom = (powerMeasI / 2 + powerMeasQ / 2) / 128;
		qCoffDenom = powerMeasQ / 64;

		if ((powerMeasQ != 0) && (iCoffDenom != 0) &&
		    (qCoffDenom != 0)) {
			iCoff = iqCorrMeas / iCoffDenom;
			qCoff = powerMeasI / qCoffDenom - 64;
			ath_dbg(common, CALIBRATE, "Chn %d iCoff = 0x%08x\n",
				i, iCoff);
			ath_dbg(common, CALIBRATE, "Chn %d qCoff = 0x%08x\n",
				i, qCoff);

			iCoff = iCoff & 0x3f;
			ath_dbg(common, CALIBRATE,
				"New: Chn %d iCoff = 0x%08x\n", i, iCoff);
			if (iqCorrNeg == 0x0)
				iCoff = 0x40 - iCoff;

			if (qCoff > 15)
				qCoff = 15;
			else if (qCoff <= -16)
				qCoff = -16;

			ath_dbg(common, CALIBRATE,
				"Chn %d : iCoff = 0x%x  qCoff = 0x%x\n",
				i, iCoff, qCoff);

			REG_RMW_FIELD(ah, AR_PHY_TIMING_CTRL4(i),
				      AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF,
				      iCoff);
			REG_RMW_FIELD(ah, AR_PHY_TIMING_CTRL4(i),
				      AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF,
				      qCoff);
			ath_dbg(common, CALIBRATE,
				"IQ Cal and Correction done for Chain %d\n",
				i);
		}
	}

	REG_SET_BIT(ah, AR_PHY_TIMING_CTRL4(0),
		    AR_PHY_TIMING_CTRL4_IQCORR_ENABLE);
}