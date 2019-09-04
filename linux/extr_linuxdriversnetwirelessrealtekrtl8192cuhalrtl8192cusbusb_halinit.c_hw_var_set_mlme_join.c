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
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */

__attribute__((used)) static void hw_var_set_mlme_join(PADAPTER Adapter, u8 variable, u8* val)
{
#ifdef CONFIG_CONCURRENT_MODE
	u8	RetryLimit = 0x30;
	u8	type = *((u8 *)val);
	HAL_DATA_TYPE *pHalData = GET_HAL_DATA(Adapter);
	struct mlme_priv	*pmlmepriv = &Adapter->mlmepriv;

	if(type == 0) // prepare to join
	{		
		if(check_buddy_mlmeinfo_state(Adapter, WIFI_FW_AP_STATE) &&
			check_buddy_fwstate(Adapter, _FW_LINKED))		
		{
			StopTxBeacon(Adapter);
		}
	
		//enable to rx data frame.Accept all data frame
		//rtw_write32(padapter, REG_RCR, rtw_read32(padapter, REG_RCR)|RCR_ADF);
		rtw_write16(Adapter, REG_RXFLTMAP2,0xFFFF);

		if(check_buddy_mlmeinfo_state(Adapter, WIFI_FW_AP_STATE))
			rtw_write32(Adapter, REG_RCR, rtw_read32(Adapter, REG_RCR)|RCR_CBSSID_BCN);
		else
			rtw_write32(Adapter, REG_RCR, rtw_read32(Adapter, REG_RCR)|RCR_CBSSID_DATA|RCR_CBSSID_BCN);

		if(check_fwstate(pmlmepriv, WIFI_STATION_STATE) == _TRUE)
		{
			RetryLimit = (pHalData->CustomerID == RT_CID_CCX) ? 7 : 48;
		}
		else // Ad-hoc Mode
		{
			RetryLimit = 0x7;
		}
	}
	else if(type == 1) //joinbss_event call back when join res < 0
	{		
		if(check_buddy_mlmeinfo_state(Adapter, _HW_STATE_NOLINK_))		
			rtw_write16(Adapter, REG_RXFLTMAP2,0x00);

		if(check_buddy_mlmeinfo_state(Adapter, WIFI_FW_AP_STATE) &&
			check_buddy_fwstate(Adapter, _FW_LINKED))
		{
			ResumeTxBeacon(Adapter);			
			
			//reset TSF 1/2 after ResumeTxBeacon
			//rtw_write8(Adapter, REG_DUAL_TSF_RST, BIT(1)|BIT(0));	
			
		}
	}
	else if(type == 2) //sta add event call back
	{
	 
		//enable update TSF
		if(Adapter->iface_type == IFACE_PORT1)
			rtw_write8(Adapter, REG_BCN_CTRL_1, rtw_read8(Adapter, REG_BCN_CTRL_1)&(~BIT(4)));
		else
			rtw_write8(Adapter, REG_BCN_CTRL, rtw_read8(Adapter, REG_BCN_CTRL)&(~BIT(4)));
		 
	
		if(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE))
		{
			//fixed beacon issue for 8191su...........
			rtw_write8(Adapter,0x542 ,0x02);
			RetryLimit = 0x7;
		}


		if(check_buddy_mlmeinfo_state(Adapter, WIFI_FW_AP_STATE) &&
			check_buddy_fwstate(Adapter, _FW_LINKED))
		{
			ResumeTxBeacon(Adapter);
			
			//reset TSF 1/2 after ResumeTxBeacon
			//rtw_write8(Adapter, REG_DUAL_TSF_RST, BIT(1)|BIT(0));
		}
		
	}

	rtw_write16(Adapter, REG_RL, RetryLimit << RETRY_LIMIT_SHORT_SHIFT | RetryLimit << RETRY_LIMIT_LONG_SHIFT);
	
#endif
}