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
struct hal_com_data {scalar_t__**** TxPwrByRateOffset; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t BAND_ON_2_4G ; 
 size_t BAND_ON_5G ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t TX_PWR_BY_RATE_NUM_RATE ; 
 size_t TX_PWR_BY_RATE_NUM_RF ; 

void PHY_InitTxPowerByRate(struct adapter *padapter)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 band, rfPath, TxNum, rate;

	for (band = BAND_ON_2_4G; band <= BAND_ON_5G; ++band)
			for (rfPath = 0; rfPath < TX_PWR_BY_RATE_NUM_RF; ++rfPath)
				for (TxNum = 0; TxNum < TX_PWR_BY_RATE_NUM_RF; ++TxNum)
					for (rate = 0; rate < TX_PWR_BY_RATE_NUM_RATE; ++rate)
						pHalData->TxPwrByRateOffset[band][rfPath][TxNum][rate] = 0;
}