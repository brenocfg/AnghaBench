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
struct hal_com_data {int /*<<< orphan*/ **** TxPwrByRateOffset; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 size_t BAND_ON_5G ; 
 int /*<<< orphan*/  DBG_871X (char*,size_t) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  MGN_VHT2SS_MCS0 ; 
 int /*<<< orphan*/  MGN_VHT2SS_MCS1 ; 
 size_t ODM_RF_PATH_D ; 
 size_t PHY_GetRateIndexOfTxPowerByRate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_GetRateValuesOfTxPowerByRate (struct adapter*,size_t,size_t,size_t,size_t*,int /*<<< orphan*/ *,size_t*) ; 
 size_t RF_2TX ; 

__attribute__((used)) static void PHY_StoreTxPowerByRateNew(
	struct adapter *padapter,
	u32	Band,
	u32	RfPath,
	u32	TxNum,
	u32	RegAddr,
	u32	BitMask,
	u32	Data
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 i = 0, rateIndex[4] = {0}, rateNum = 0;
	s8	PwrByRateVal[4] = {0};

	PHY_GetRateValuesOfTxPowerByRate(padapter, RegAddr, BitMask, Data, rateIndex, PwrByRateVal, &rateNum);

	if (Band != BAND_ON_2_4G && Band != BAND_ON_5G) {
		DBG_871X("Invalid Band %d\n", Band);
		return;
	}

	if (RfPath > ODM_RF_PATH_D) {
		DBG_871X("Invalid RfPath %d\n", RfPath);
		return;
	}

	if (TxNum > ODM_RF_PATH_D) {
		DBG_871X("Invalid TxNum %d\n", TxNum);
		return;
	}

	for (i = 0; i < rateNum; ++i) {
		if (rateIndex[i] == PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS0) ||
			 rateIndex[i] == PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS1))
			TxNum = RF_2TX;

		pHalData->TxPwrByRateOffset[Band][RfPath][TxNum][rateIndex[i]] = PwrByRateVal[i];
	}
}