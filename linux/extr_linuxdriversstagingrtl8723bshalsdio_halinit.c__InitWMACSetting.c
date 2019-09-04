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
typedef  int u16 ;
struct hal_com_data {int ReceiveConfig; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int RCR_AB ; 
 int RCR_AM ; 
 int RCR_AMF ; 
 int RCR_APM ; 
 int RCR_APP_ICV ; 
 int RCR_APP_MIC ; 
 int RCR_APP_PHYST_RXFF ; 
 int RCR_CBSSID_BCN ; 
 int RCR_CBSSID_DATA ; 
 int RCR_HTC_LOC_CTRL ; 
 scalar_t__ REG_MAR ; 
 scalar_t__ REG_RCR ; 
 int /*<<< orphan*/  REG_RXFLTMAP0 ; 
 int /*<<< orphan*/  REG_RXFLTMAP1 ; 
 int /*<<< orphan*/  REG_RXFLTMAP2 ; 
 int /*<<< orphan*/  rtw_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void _InitWMACSetting(struct adapter *padapter)
{
	struct hal_com_data *pHalData;
	u16 value16;


	pHalData = GET_HAL_DATA(padapter);

	pHalData->ReceiveConfig = 0;
	pHalData->ReceiveConfig |= RCR_APM | RCR_AM | RCR_AB;
	pHalData->ReceiveConfig |= RCR_CBSSID_DATA | RCR_CBSSID_BCN | RCR_AMF;
	pHalData->ReceiveConfig |= RCR_HTC_LOC_CTRL;
	pHalData->ReceiveConfig |= RCR_APP_PHYST_RXFF | RCR_APP_ICV | RCR_APP_MIC;
	rtw_write32(padapter, REG_RCR, pHalData->ReceiveConfig);

	/*  Accept all multicast address */
	rtw_write32(padapter, REG_MAR, 0xFFFFFFFF);
	rtw_write32(padapter, REG_MAR + 4, 0xFFFFFFFF);

	/*  Accept all data frames */
	value16 = 0xFFFF;
	rtw_write16(padapter, REG_RXFLTMAP2, value16);

	/*  2010.09.08 hpfan */
	/*  Since ADF is removed from RCR, ps-poll will not be indicate to driver, */
	/*  RxFilterMap should mask ps-poll to gurantee AP mode can rx ps-poll. */
	value16 = 0x400;
	rtw_write16(padapter, REG_RXFLTMAP1, value16);

	/*  Accept all management frames */
	value16 = 0xFFFF;
	rtw_write16(padapter, REG_RXFLTMAP0, value16);
}