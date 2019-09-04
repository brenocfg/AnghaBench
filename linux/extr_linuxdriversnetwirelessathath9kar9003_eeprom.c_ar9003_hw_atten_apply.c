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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ alt_mingainidx; scalar_t__ xatten_margin_cfg; } ;
struct ath_hw {int rxchainmask; int txchainmask; TYPE_1__ config; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 unsigned long AR_PHY_EXT_ATTEN_CTL_0 ; 
 unsigned long AR_PHY_EXT_ATTEN_CTL_1 ; 
 unsigned long AR_PHY_EXT_ATTEN_CTL_2 ; 
 int /*<<< orphan*/  AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int ar9003_hw_atten_chain_get (struct ath_hw*,int,struct ath9k_channel*) ; 
 int ar9003_hw_atten_chain_get_margin (struct ath_hw*,int,struct ath9k_channel*) ; 
 scalar_t__ ar9003_hw_get_rx_gain_idx (struct ath_hw*) ; 

__attribute__((used)) static void ar9003_hw_atten_apply(struct ath_hw *ah, struct ath9k_channel *chan)
{
	int i;
	u16 value;
	unsigned long ext_atten_reg[3] = {AR_PHY_EXT_ATTEN_CTL_0,
					  AR_PHY_EXT_ATTEN_CTL_1,
					  AR_PHY_EXT_ATTEN_CTL_2,
					 };

	if ((AR_SREV_9462(ah)) && (ah->rxchainmask == 0x2)) {
		value = ar9003_hw_atten_chain_get(ah, 1, chan);
		REG_RMW_FIELD(ah, ext_atten_reg[0],
			      AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB, value);

		value = ar9003_hw_atten_chain_get_margin(ah, 1, chan);
		REG_RMW_FIELD(ah, ext_atten_reg[0],
			      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
			      value);
	}

	/* Test value. if 0 then attenuation is unused. Don't load anything. */
	for (i = 0; i < 3; i++) {
		if (ah->txchainmask & BIT(i)) {
			value = ar9003_hw_atten_chain_get(ah, i, chan);
			REG_RMW_FIELD(ah, ext_atten_reg[i],
				      AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB, value);

			if (AR_SREV_9485(ah) &&
			    (ar9003_hw_get_rx_gain_idx(ah) == 0) &&
			    ah->config.xatten_margin_cfg)
				value = 5;
			else
				value = ar9003_hw_atten_chain_get_margin(ah, i, chan);

			if (ah->config.alt_mingainidx)
				REG_RMW_FIELD(ah, AR_PHY_EXT_ATTEN_CTL_0,
					      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
					      value);

			REG_RMW_FIELD(ah, ext_atten_reg[i],
				      AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
				      value);
		}
	}
}