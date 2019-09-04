#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u16 ;
struct TYPE_5__ {int NumRxOkInPeriod; int NumTxOkInPeriod; void* bHigherBusyTxTraffic; void* bHigherBusyRxTraffic; void* bHigherBusyTraffic; void* bRxBusyTraffic; void* bTxBusyTraffic; void* bBusyTraffic; scalar_t__ NumRxUnicastOkInPeriod; } ;
struct mlme_priv {TYPE_2__ LinkDetectInfo; } ;
struct TYPE_4__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  TYPE_2__ RT_LINK_DETECT_T ;

/* Variables and functions */
 void* _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void traffic_status_watchdog(_adapter *padapter)
{
#ifdef CONFIG_LPS
	u8	bEnterPS;
#endif
	u16	BusyThreshold = 100;
	u8	bBusyTraffic = _FALSE, bTxBusyTraffic = _FALSE, bRxBusyTraffic = _FALSE;
	u8	bHigherBusyTraffic = _FALSE, bHigherBusyRxTraffic = _FALSE, bHigherBusyTxTraffic = _FALSE;
	struct mlme_priv		*pmlmepriv = &(padapter->mlmepriv);
#ifdef CONFIG_TDLS
	struct tdls_info *ptdlsinfo = &(padapter->tdlsinfo);
#endif //CONFIG_TDLS

	RT_LINK_DETECT_T * link_detect = &pmlmepriv->LinkDetectInfo;

	//
	// Determine if our traffic is busy now
	//
	if((check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE) 
		/*&& !MgntInitAdapterInProgress(pMgntInfo)*/)
	{

		// if we raise bBusyTraffic in last watchdog, using lower threshold.
		if (pmlmepriv->LinkDetectInfo.bBusyTraffic)
			BusyThreshold = 75;
		if( pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > BusyThreshold ||
			pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > BusyThreshold )
		{
			bBusyTraffic = _TRUE;

			if(pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > BusyThreshold)
				bRxBusyTraffic = _TRUE;

			if(pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > BusyThreshold)
				bTxBusyTraffic = _TRUE;
		}

		// Higher Tx/Rx data.
		if( pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > 4000 ||
			pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > 4000 )
		{
			bHigherBusyTraffic = _TRUE;

			// Extremely high Rx data.
			if(pmlmepriv->LinkDetectInfo.NumRxOkInPeriod > 5000)
				bHigherBusyRxTraffic = _TRUE;

			// Extremely high Tx data.
			if(pmlmepriv->LinkDetectInfo.NumTxOkInPeriod > 5000)
				bHigherBusyTxTraffic = _TRUE;
		}

#ifdef CONFIG_TRAFFIC_PROTECT
#define TX_ACTIVE_TH 2
#define RX_ACTIVE_TH 1
#define TRAFFIC_PROTECT_PERIOD_MS 4500

	if (link_detect->NumTxOkInPeriod > TX_ACTIVE_TH
		|| link_detect->NumRxUnicastOkInPeriod > RX_ACTIVE_TH) {

		LOG_LEVEL(_drv_info_, FUNC_ADPT_FMT" acqiure wake_lock for %u ms(tx:%d,rx_unicast:%d)\n",
			FUNC_ADPT_ARG(padapter),
			TRAFFIC_PROTECT_PERIOD_MS,
			link_detect->NumTxOkInPeriod,
			link_detect->NumRxUnicastOkInPeriod);

		rtw_lock_suspend_timeout(TRAFFIC_PROTECT_PERIOD_MS);
	}
#endif

#ifdef CONFIG_TDLS
#ifdef CONFIG_TDLS_AUTOSETUP
		if( ( ptdlsinfo->watchdog_count % TDLS_WATCHDOG_PERIOD ) == 0 )	//TDLS_WATCHDOG_PERIOD * 2sec, periodically sending
			issue_tdls_dis_req( padapter, NULL );
		ptdlsinfo->watchdog_count++;
#endif //CONFIG_TDLS_AUTOSETUP
#endif //CONFIG_TDLS

#ifdef CONFIG_LPS
		// check traffic for  powersaving.
		if( ((pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod + pmlmepriv->LinkDetectInfo.NumTxOkInPeriod) > 8 ) ||
			(pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod > 2) )
		{
			//DBG_871X("Tx = %d, Rx = %d \n",pmlmepriv->LinkDetectInfo.NumTxOkInPeriod,pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod);
			bEnterPS= _FALSE;
		}
		else
		{
			bEnterPS= _TRUE;
		}

		// LeisurePS only work in infra mode.
		if(bEnterPS)
		{
			LPS_Enter(padapter);
		}
		else
		{
			LPS_Leave(padapter);
		}
#endif
	}
	else
	{
#ifdef CONFIG_LPS
		LPS_Leave(padapter);
#endif
	}

	pmlmepriv->LinkDetectInfo.NumRxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumTxOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod = 0;
	pmlmepriv->LinkDetectInfo.bBusyTraffic = bBusyTraffic;
	pmlmepriv->LinkDetectInfo.bTxBusyTraffic = bTxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bRxBusyTraffic = bRxBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTraffic = bHigherBusyTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyRxTraffic = bHigherBusyRxTraffic;
	pmlmepriv->LinkDetectInfo.bHigherBusyTxTraffic = bHigherBusyTxTraffic;
	
}