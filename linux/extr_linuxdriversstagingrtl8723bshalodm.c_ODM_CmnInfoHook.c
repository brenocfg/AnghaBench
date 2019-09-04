#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* mp_mode; void* pu1ForcedIgiLb; void* pForcedDataRate; void* pbNet_closed; void* pAntennaTest; void* pinit_adpt_in_progress; void* pbDriverIsGoingToPnpSetPowerSleep; void* pbDriverStopped; void* pOnePathCCA; void* pbPowerSaving; void* pbScanInProcess; void* pbMasterOfDMSP; void* pBuddyAdapter; void* pbGetValueFromOtherMac; void* pChannel; void* pBandWidth; void* pSecurity; void* pSecChOffset; void* pBandType; void* pwirelessmode; void* pNumRxBytesUnicast; void* pNumTxBytesUnicast; void* pMacPhyMode; } ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  int ODM_CMNINFO_E ;

/* Variables and functions */
#define  ODM_CMNINFO_ANT_TEST 150 
#define  ODM_CMNINFO_BAND 149 
#define  ODM_CMNINFO_BUDDY_ADAPTOR 148 
#define  ODM_CMNINFO_BW 147 
#define  ODM_CMNINFO_CHNL 146 
#define  ODM_CMNINFO_DMSP_GET_VALUE 145 
#define  ODM_CMNINFO_DMSP_IS_MASTER 144 
#define  ODM_CMNINFO_DRV_STOP 143 
#define  ODM_CMNINFO_FORCED_IGI_LB 142 
#define  ODM_CMNINFO_FORCED_RATE 141 
#define  ODM_CMNINFO_INIT_ON 140 
#define  ODM_CMNINFO_MAC_PHY_MODE 139 
#define  ODM_CMNINFO_MP_MODE 138 
#define  ODM_CMNINFO_NET_CLOSED 137 
#define  ODM_CMNINFO_ONE_PATH_CCA 136 
#define  ODM_CMNINFO_PNP_IN 135 
#define  ODM_CMNINFO_POWER_SAVING 134 
#define  ODM_CMNINFO_RX_UNI 133 
#define  ODM_CMNINFO_SCAN 132 
#define  ODM_CMNINFO_SEC_CHNL_OFFSET 131 
#define  ODM_CMNINFO_SEC_MODE 130 
#define  ODM_CMNINFO_TX_UNI 129 
#define  ODM_CMNINFO_WM_MODE 128 

void ODM_CmnInfoHook(PDM_ODM_T pDM_Odm, ODM_CMNINFO_E CmnInfo, void *pValue)
{
	/*  */
	/*  Hook call by reference pointer. */
	/*  */
	switch (CmnInfo) {
	/*  */
	/*  Dynamic call by reference pointer. */
	/*  */
	case ODM_CMNINFO_MAC_PHY_MODE:
		pDM_Odm->pMacPhyMode = pValue;
		break;

	case ODM_CMNINFO_TX_UNI:
		pDM_Odm->pNumTxBytesUnicast = pValue;
		break;

	case ODM_CMNINFO_RX_UNI:
		pDM_Odm->pNumRxBytesUnicast = pValue;
		break;

	case ODM_CMNINFO_WM_MODE:
		pDM_Odm->pwirelessmode = pValue;
		break;

	case ODM_CMNINFO_BAND:
		pDM_Odm->pBandType = pValue;
		break;

	case ODM_CMNINFO_SEC_CHNL_OFFSET:
		pDM_Odm->pSecChOffset = pValue;
		break;

	case ODM_CMNINFO_SEC_MODE:
		pDM_Odm->pSecurity = pValue;
		break;

	case ODM_CMNINFO_BW:
		pDM_Odm->pBandWidth = pValue;
		break;

	case ODM_CMNINFO_CHNL:
		pDM_Odm->pChannel = pValue;
		break;

	case ODM_CMNINFO_DMSP_GET_VALUE:
		pDM_Odm->pbGetValueFromOtherMac = pValue;
		break;

	case ODM_CMNINFO_BUDDY_ADAPTOR:
		pDM_Odm->pBuddyAdapter = pValue;
		break;

	case ODM_CMNINFO_DMSP_IS_MASTER:
		pDM_Odm->pbMasterOfDMSP = pValue;
		break;

	case ODM_CMNINFO_SCAN:
		pDM_Odm->pbScanInProcess = pValue;
		break;

	case ODM_CMNINFO_POWER_SAVING:
		pDM_Odm->pbPowerSaving = pValue;
		break;

	case ODM_CMNINFO_ONE_PATH_CCA:
		pDM_Odm->pOnePathCCA = pValue;
		break;

	case ODM_CMNINFO_DRV_STOP:
		pDM_Odm->pbDriverStopped =  pValue;
		break;

	case ODM_CMNINFO_PNP_IN:
		pDM_Odm->pbDriverIsGoingToPnpSetPowerSleep =  pValue;
		break;

	case ODM_CMNINFO_INIT_ON:
		pDM_Odm->pinit_adpt_in_progress =  pValue;
		break;

	case ODM_CMNINFO_ANT_TEST:
		pDM_Odm->pAntennaTest =  pValue;
		break;

	case ODM_CMNINFO_NET_CLOSED:
		pDM_Odm->pbNet_closed = pValue;
		break;

	case ODM_CMNINFO_FORCED_RATE:
		pDM_Odm->pForcedDataRate = pValue;
		break;

	case ODM_CMNINFO_FORCED_IGI_LB:
		pDM_Odm->pu1ForcedIgiLb = pValue;
		break;

	case ODM_CMNINFO_MP_MODE:
		pDM_Odm->mp_mode = pValue;
		break;

	/* case ODM_CMNINFO_RTSTA_AID: */
	/* pDM_Odm->pAidMap =  (u8 *)pValue; */
	/* break; */

	/* case ODM_CMNINFO_BT_COEXIST: */
	/* pDM_Odm->BTCoexist = (bool *)pValue; */

	/* case ODM_CMNINFO_STA_STATUS: */
	/* pDM_Odm->pODM_StaInfo[] = (PSTA_INFO_T)pValue; */
	/* break; */

	/* case ODM_CMNINFO_PHY_STATUS: */
	/* pDM_Odm->pPhyInfo = (ODM_PHY_INFO *)pValue; */
	/* break; */

	/* case ODM_CMNINFO_MAC_STATUS: */
	/* pDM_Odm->pMacInfo = (ODM_MAC_INFO *)pValue; */
	/* break; */
	/* To remove the compiler warning, must add an empty default statement to handle the other values. */
	default:
		/* do nothing */
		break;
	}

}