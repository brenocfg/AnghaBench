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
struct dm_priv {scalar_t__ DynamicTxHighPowerLvl; } ;
struct hal_data_8188e {int EEPROMRegulatory; int** MCSTxPowerLevelOriginalOffset; int pwrGroupCnt; int PGMaxGroup; int** TxPwrLegacyHtDiff; int** TxPwrHt20Diff; int** PwrGroupHT40; int** PwrGroupHT20; int /*<<< orphan*/  CurrentChannelBW; struct dm_priv dmpriv; } ;
struct adapter {struct hal_data_8188e* HalData; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_40 ; 
 scalar_t__ TxHighPwrLevel_Level1 ; 
 scalar_t__ TxHighPwrLevel_Level2 ; 

__attribute__((used)) static void get_rx_power_val_by_reg(struct adapter *adapt, u8 channel,
				    u8 index, u32 *powerbase0, u32 *powerbase1,
				    u32 *out_val)
{
	struct hal_data_8188e *hal_data = adapt->HalData;
	struct dm_priv	*pdmpriv = &hal_data->dmpriv;
	u8 i, chnlGroup = 0, pwr_diff_limit[4], customer_pwr_limit;
	s8 pwr_diff = 0;
	u32 write_val, customer_limit, rf;
	u8 regulatory = hal_data->EEPROMRegulatory;

	/*  Index 0 & 1= legacy OFDM, 2-5=HT_MCS rate */

	for (rf = 0; rf < 2; rf++) {
		u8 j = index + (rf ? 8 : 0);

		switch (regulatory) {
		case 0:
			chnlGroup = 0;
			write_val = hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][index+(rf ? 8 : 0)] +
				((index < 2) ? powerbase0[rf] : powerbase1[rf]);
			break;
		case 1: /*  Realtek regulatory */
			/*  increase power diff defined by Realtek for regulatory */
			if (hal_data->pwrGroupCnt == 1)
				chnlGroup = 0;
			if (hal_data->pwrGroupCnt >= hal_data->PGMaxGroup) {
				if (channel < 3)
					chnlGroup = 0;
				else if (channel < 6)
					chnlGroup = 1;
				else if (channel < 9)
					chnlGroup = 2;
				else if (channel < 12)
					chnlGroup = 3;
				else if (channel < 14)
					chnlGroup = 4;
				else if (channel == 14)
					chnlGroup = 5;
			}
			write_val = hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][index+(rf ? 8 : 0)] +
					((index < 2) ? powerbase0[rf] : powerbase1[rf]);
			break;
		case 2:	/*  Better regulatory */
				/*  don't increase any power diff */
			write_val = (index < 2) ? powerbase0[rf] : powerbase1[rf];
			break;
		case 3:	/*  Customer defined power diff. */
				/*  increase power diff defined by customer. */
			chnlGroup = 0;

			if (index < 2)
				pwr_diff = hal_data->TxPwrLegacyHtDiff[rf][channel-1];
			else if (hal_data->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
				pwr_diff = hal_data->TxPwrHt20Diff[rf][channel-1];

			if (hal_data->CurrentChannelBW == HT_CHANNEL_WIDTH_40)
				customer_pwr_limit = hal_data->PwrGroupHT40[rf][channel-1];
			else
				customer_pwr_limit = hal_data->PwrGroupHT20[rf][channel-1];

			if (pwr_diff >= customer_pwr_limit)
				pwr_diff = 0;
			else
				pwr_diff = customer_pwr_limit - pwr_diff;

			for (i = 0; i < 4; i++) {
				pwr_diff_limit[i] = (u8)((hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][j] &
							 (0x7f << (i * 8))) >> (i * 8));

				if (pwr_diff_limit[i] > pwr_diff)
					pwr_diff_limit[i] = pwr_diff;
			}
			customer_limit = (pwr_diff_limit[3]<<24) |
					 (pwr_diff_limit[2]<<16) |
					 (pwr_diff_limit[1]<<8) |
					 (pwr_diff_limit[0]);
			write_val = customer_limit + ((index < 2) ? powerbase0[rf] : powerbase1[rf]);
			break;
		default:
			chnlGroup = 0;
			write_val = hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][j] +
					((index < 2) ? powerbase0[rf] : powerbase1[rf]);
			break;
		}
/*  20100427 Joseph: Driver dynamic Tx power shall not affect Tx power. It shall be determined by power training mechanism. */
/*  Currently, we cannot fully disable driver dynamic tx power mechanism because it is referenced by BT coexist mechanism. */
/*  In the future, two mechanism shall be separated from each other and maintained independently. Thanks for Lanhsin's reminder. */
		/* 92d do not need this */
		if (pdmpriv->DynamicTxHighPowerLvl == TxHighPwrLevel_Level1)
			write_val = 0x14141414;
		else if (pdmpriv->DynamicTxHighPowerLvl == TxHighPwrLevel_Level2)
			write_val = 0x00000000;

		*(out_val+rf) = write_val;
	}
}