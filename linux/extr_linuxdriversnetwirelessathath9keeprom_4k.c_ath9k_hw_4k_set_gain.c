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
typedef  int /*<<< orphan*/  u8 ;
struct modal_eep_4k_header {int /*<<< orphan*/ * rxTxMarginCh; int /*<<< orphan*/ * xatten2Db; int /*<<< orphan*/ * xatten2Margin; int /*<<< orphan*/ * bswAtten; int /*<<< orphan*/ * bswMargin; int /*<<< orphan*/ * txRxAttenCh; int /*<<< orphan*/ * iqCalQCh; int /*<<< orphan*/ * iqCalICh; int /*<<< orphan*/ * antCtrlChain; } ;
struct ath_hw {int dummy; } ;
struct ar5416_eeprom_4k {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR5416_EEP_MINOR_VER_3 ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_ATTEN ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_MARGIN ; 
 scalar_t__ AR_PHY_GAIN_2GHZ ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN2_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN ; 
 scalar_t__ AR_PHY_RXGAIN ; 
 int /*<<< orphan*/  AR_PHY_SWITCH_CHAIN_0 ; 
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4 (int /*<<< orphan*/ ) ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF ; 
 int /*<<< orphan*/  ENABLE_REG_RMW_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_RMW_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SM (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ath9k_hw_4k_get_eeprom_rev (struct ath_hw*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hw_4k_set_gain(struct ath_hw *ah,
				 struct modal_eep_4k_header *pModal,
				 struct ar5416_eeprom_4k *eep,
				 u8 txRxAttenLocal)
{
	ENABLE_REG_RMW_BUFFER(ah);
	REG_RMW(ah, AR_PHY_SWITCH_CHAIN_0,
		le32_to_cpu(pModal->antCtrlChain[0]), 0);

	REG_RMW(ah, AR_PHY_TIMING_CTRL4(0),
		SM(pModal->iqCalICh[0], AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF) |
		SM(pModal->iqCalQCh[0], AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF),
		AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF | AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF);

	if (ath9k_hw_4k_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_3) {
		txRxAttenLocal = pModal->txRxAttenCh[0];

		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN, pModal->bswMargin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB, pModal->bswAtten[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB, pModal->xatten2Db[0]);

		/* Set the block 1 value to block 0 value */
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB, pModal->bswAtten[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[0]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + 0x1000,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB,
			      pModal->xatten2Db[0]);
	}

	REG_RMW_FIELD(ah, AR_PHY_RXGAIN,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
	REG_RMW_FIELD(ah, AR_PHY_RXGAIN,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[0]);

	REG_RMW_FIELD(ah, AR_PHY_RXGAIN + 0x1000,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
	REG_RMW_FIELD(ah, AR_PHY_RXGAIN + 0x1000,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[0]);
	REG_RMW_BUFFER_FLUSH(ah);
}