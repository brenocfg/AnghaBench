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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _FALSE ; 

unsigned int send_beacon(_adapter *padapter)
{
	u8	bxmitok = _FALSE;
	int	issue=0;
	int poll = 0;
//#ifdef CONFIG_CONCURRENT_MODE
	//struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	//struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	//_adapter *pbuddy_adapter = padapter->pbuddy_adapter;
	//struct mlme_priv *pbuddy_mlmepriv = &(pbuddy_adapter->mlmepriv);
//#endif		

#ifdef CONFIG_PCI_HCI

	//DBG_871X("%s\n", __FUNCTION__);

	issue_beacon(padapter);

	return _SUCCESS;

#endif

#if defined(CONFIG_USB_HCI) || defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
	u32 start = rtw_get_current_time();

	rtw_hal_set_hwreg(padapter, HW_VAR_BCN_VALID, NULL);
	do{
		issue_beacon(padapter);
		issue++;
		do {
			rtw_yield_os();
			rtw_hal_get_hwreg(padapter, HW_VAR_BCN_VALID, (u8 *)(&bxmitok));
			poll++;
		}while((poll%10)!=0 && _FALSE == bxmitok && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

	}while(_FALSE == bxmitok && issue<100 && !padapter->bSurpriseRemoved && !padapter->bDriverStopped);

	if(padapter->bSurpriseRemoved || padapter->bDriverStopped)
	{
		return _FAIL;
	}
	if(_FALSE == bxmitok)
	{
		DBG_871X("%s fail! %u ms\n", __FUNCTION__, rtw_get_passing_time_ms(start));
		return _FAIL;
	}
	else
	{
		u32 passing_time = rtw_get_passing_time_ms(start);

		if(passing_time > 100 || issue > 3)
			DBG_871X("%s success, issue:%d, poll:%d, %u ms\n", __FUNCTION__, issue, poll, rtw_get_passing_time_ms(start));
		//else
		//	DBG_871X("%s success, issue:%d, poll:%d, %u ms\n", __FUNCTION__, issue, poll, rtw_get_passing_time_ms(start));
		
		return _SUCCESS;
	}

#endif

}