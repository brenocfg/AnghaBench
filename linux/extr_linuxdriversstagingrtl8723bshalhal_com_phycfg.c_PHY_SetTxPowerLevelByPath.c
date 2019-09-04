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
struct hal_com_data {scalar_t__ CurrentBandType; int NumTotalRFPath; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 int /*<<< orphan*/  CCK ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  HT_MCS0_MCS7 ; 
 int /*<<< orphan*/  HT_MCS8_MCS15 ; 
 int /*<<< orphan*/  OFDM ; 
 int /*<<< orphan*/  PHY_SetTxPowerIndexByRateSection (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PHY_SetTxPowerLevelByPath(struct adapter *Adapter, u8 channel, u8 path)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	bool bIsIn24G = (pHalData->CurrentBandType == BAND_ON_2_4G);

	/* if (pMgntInfo->RegNByteAccess == 0) */
	{
		if (bIsIn24G)
			PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, CCK);

		PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, OFDM);
		PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, HT_MCS0_MCS7);

		if (pHalData->NumTotalRFPath >= 2)
			PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, HT_MCS8_MCS15);

	}
}