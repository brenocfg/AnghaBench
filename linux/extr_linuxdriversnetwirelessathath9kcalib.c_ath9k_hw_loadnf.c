#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ath_hw {int rxchainmask; int nf_override; int /*<<< orphan*/ * nf_regs; TYPE_1__* caldata; } ;
struct ath_common {int dummy; } ;
struct ath9k_nfcal_hist {int privNF; } ;
struct ath9k_channel {int dummy; } ;
typedef  int s16 ;
struct TYPE_4__ {int nominal; int* cal; } ;
struct TYPE_3__ {struct ath9k_nfcal_hist* nfCalHist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY ; 
 unsigned int AR5416_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int AR_PHY_AGC_CONTROL_ENABLE_NF ; 
 int AR_PHY_AGC_CONTROL_NF ; 
 int AR_PHY_AGC_CONTROL_NO_UPDATE_NF ; 
 int /*<<< orphan*/  ENABLE_REG_RMW_BUFFER (struct ath_hw*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IS_CHAN_HT40 (struct ath9k_channel*) ; 
 unsigned int NUM_NF_READINGS ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_RMW_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 TYPE_2__* ath9k_hw_get_nf_limits (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ath9k_hw_loadnf(struct ath_hw *ah, struct ath9k_channel *chan)
{
	struct ath9k_nfcal_hist *h = NULL;
	unsigned i, j;
	u8 chainmask = (ah->rxchainmask << 3) | ah->rxchainmask;
	struct ath_common *common = ath9k_hw_common(ah);
	s16 default_nf = ath9k_hw_get_nf_limits(ah, chan)->nominal;
	u32 bb_agc_ctl = REG_READ(ah, AR_PHY_AGC_CONTROL);

	if (ah->caldata)
		h = ah->caldata->nfCalHist;

	ENABLE_REG_RMW_BUFFER(ah);
	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (chainmask & (1 << i)) {
			s16 nfval;

			if ((i >= AR5416_MAX_CHAINS) && !IS_CHAN_HT40(chan))
				continue;

			if (ah->nf_override)
				nfval = ah->nf_override;
			else if (h)
				nfval = h[i].privNF;
			else {
				/* Try to get calibrated noise floor value */
				nfval =
				    ath9k_hw_get_nf_limits(ah, chan)->cal[i];
				if (nfval > -60 || nfval < -127)
					nfval = default_nf;
			}

			REG_RMW(ah, ah->nf_regs[i],
				(((u32) nfval << 1) & 0x1ff), 0x1ff);
		}
	}

	/*
	 * stop NF cal if ongoing to ensure NF load completes immediately
	 * (or after end rx/tx frame if ongoing)
	 */
	if (bb_agc_ctl & AR_PHY_AGC_CONTROL_NF) {
		REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);
		REG_RMW_BUFFER_FLUSH(ah);
		ENABLE_REG_RMW_BUFFER(ah);
	}

	/*
	 * Load software filtered NF value into baseband internal minCCApwr
	 * variable.
	 */
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_ENABLE_NF);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);
	REG_RMW_BUFFER_FLUSH(ah);

	/*
	 * Wait for load to complete, should be fast, a few 10s of us.
	 * The max delay was changed from an original 250us to 22.2 msec.
	 * This would increase timeout to the longest possible frame
	 * (11n max length 22.1 msec)
	 */
	for (j = 0; j < 22200; j++) {
		if ((REG_READ(ah, AR_PHY_AGC_CONTROL) &
			      AR_PHY_AGC_CONTROL_NF) == 0)
			break;
		udelay(10);
	}

	/*
	 * Restart NF so it can continue.
	 */
	if (bb_agc_ctl & AR_PHY_AGC_CONTROL_NF) {
		ENABLE_REG_RMW_BUFFER(ah);
		if (bb_agc_ctl & AR_PHY_AGC_CONTROL_ENABLE_NF)
			REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
				    AR_PHY_AGC_CONTROL_ENABLE_NF);
		if (bb_agc_ctl & AR_PHY_AGC_CONTROL_NO_UPDATE_NF)
			REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
				    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);
		REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);
		REG_RMW_BUFFER_FLUSH(ah);
	}

	/*
	 * We timed out waiting for the noisefloor to load, probably due to an
	 * in-progress rx. Simply return here and allow the load plenty of time
	 * to complete before the next calibration interval.  We need to avoid
	 * trying to load -50 (which happens below) while the previous load is
	 * still in progress as this can cause rx deafness. Instead by returning
	 * here, the baseband nf cal will just be capped by our present
	 * noisefloor until the next calibration timer.
	 */
	if (j == 22200) {
		ath_dbg(common, ANY,
			"Timeout while waiting for nf to load: AR_PHY_AGC_CONTROL=0x%x\n",
			REG_READ(ah, AR_PHY_AGC_CONTROL));
		return -ETIMEDOUT;
	}

	/*
	 * Restore maxCCAPower register parameter again so that we're not capped
	 * by the median we just loaded.  This will be initial (and max) value
	 * of next noise floor calibration the baseband does.
	 */
	ENABLE_REG_RMW_BUFFER(ah);
	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (chainmask & (1 << i)) {
			if ((i >= AR5416_MAX_CHAINS) && !IS_CHAN_HT40(chan))
				continue;

			REG_RMW(ah, ah->nf_regs[i],
					(((u32) (-50) << 1) & 0x1ff), 0x1ff);
		}
	}
	REG_RMW_BUFFER_FLUSH(ah);

	return 0;
}