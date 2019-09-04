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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct registry_priv {int wifi_spec; } ;
struct hal_com_data {int OutEpQueueSel; } ;
struct adapter {struct registry_priv registrypriv; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int LD_RQPN ; 
 int NORMAL_PAGE_NUM_HPQ_8723B ; 
 int NORMAL_PAGE_NUM_LPQ_8723B ; 
 int NORMAL_PAGE_NUM_NPQ_8723B ; 
 int /*<<< orphan*/  REG_RQPN ; 
 int /*<<< orphan*/  REG_RQPN_NPQ ; 
 int TX_SELE_HQ ; 
 int TX_SELE_LQ ; 
 int TX_SELE_NQ ; 
 int TX_TOTAL_PAGE_NUMBER_8723B ; 
 int WMM_NORMAL_PAGE_NUM_HPQ_8723B ; 
 int WMM_NORMAL_PAGE_NUM_LPQ_8723B ; 
 int WMM_NORMAL_PAGE_NUM_NPQ_8723B ; 
 int _HPQ (int) ; 
 int _LPQ (int) ; 
 scalar_t__ _NPQ (int) ; 
 int _PUBQ (int) ; 
 int /*<<< orphan*/  _init_available_page_threshold (struct adapter*,int,int,int,int) ; 
 int /*<<< orphan*/  rtw_hal_set_sdio_tx_max_length (struct adapter*,int,int,int,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _InitQueueReservedPage(struct adapter *padapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	u32 numHQ = 0;
	u32 numLQ = 0;
	u32 numNQ = 0;
	u32 numPubQ;
	u32 value32;
	u8 value8;
	bool bWiFiConfig	= pregistrypriv->wifi_spec;

	if (pHalData->OutEpQueueSel & TX_SELE_HQ)
		numHQ = bWiFiConfig ? WMM_NORMAL_PAGE_NUM_HPQ_8723B : NORMAL_PAGE_NUM_HPQ_8723B;

	if (pHalData->OutEpQueueSel & TX_SELE_LQ)
		numLQ = bWiFiConfig ? WMM_NORMAL_PAGE_NUM_LPQ_8723B : NORMAL_PAGE_NUM_LPQ_8723B;

	/*  NOTE: This step shall be proceed before writting REG_RQPN. */
	if (pHalData->OutEpQueueSel & TX_SELE_NQ)
		numNQ = bWiFiConfig ? WMM_NORMAL_PAGE_NUM_NPQ_8723B : NORMAL_PAGE_NUM_NPQ_8723B;

	numPubQ = TX_TOTAL_PAGE_NUMBER_8723B - numHQ - numLQ - numNQ;

	value8 = (u8)_NPQ(numNQ);
	rtw_write8(padapter, REG_RQPN_NPQ, value8);

	/*  TX DMA */
	value32 = _HPQ(numHQ) | _LPQ(numLQ) | _PUBQ(numPubQ) | LD_RQPN;
	rtw_write32(padapter, REG_RQPN, value32);

	rtw_hal_set_sdio_tx_max_length(padapter, numHQ, numNQ, numLQ, numPubQ);

	_init_available_page_threshold(padapter, numHQ, numNQ, numLQ, numPubQ);
}