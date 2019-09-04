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

__attribute__((used)) static void hw_var_set_correct_tsf(PADAPTER Adapter, u8 variable, u8* val)
{
#ifdef CONFIG_CONCURRENT_MODE
	u64	tsf;
	struct mlme_ext_priv	*pmlmeext = &Adapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	//tsf = pmlmeext->TSFValue - ((u32)pmlmeext->TSFValue % (pmlmeinfo->bcn_interval*1024)) -1024; //us
	tsf = pmlmeext->TSFValue - rtw_modular64(pmlmeext->TSFValue, (pmlmeinfo->bcn_interval*1024)) -1024; //us

	if(((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE))
	{				
		//pHalData->RegTxPause |= STOP_BCNQ;BIT(6)
		//rtw_write8(Adapter, REG_TXPAUSE, (rtw_read8(Adapter, REG_TXPAUSE)|BIT(6)));
		StopTxBeacon(Adapter);
	}

	if(Adapter->iface_type == IFACE_PORT1)
	{
		//disable related TSF function
		rtw_write8(Adapter, REG_BCN_CTRL_1, rtw_read8(Adapter, REG_BCN_CTRL_1)&(~BIT(3)));
							
		rtw_write32(Adapter, REG_TSFTR1, tsf);
		rtw_write32(Adapter, REG_TSFTR1+4, tsf>>32);

		//enable related TSF function
		rtw_write8(Adapter, REG_BCN_CTRL_1, rtw_read8(Adapter, REG_BCN_CTRL_1)|BIT(3));


#ifdef CONFIG_TSF_RESET_OFFLOAD
		// Update buddy port's TSF(TBTT) if it is SoftAP for beacon TX issue!
		if ( (pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE
			&& check_buddy_fwstate(Adapter, WIFI_AP_STATE) ) { 
			if (reset_tsf(Adapter, IFACE_PORT0) == _FALSE)
				DBG_871X("ERROR! %s()-%d: Reset port0 TSF fail\n",
					__FUNCTION__, __LINE__);
		}
#endif	// CONFIG_TSF_RESET_OFFLOAD

	}
	else	// Adapter->iface_type == IFACE_PORT1
	{
		//disable related TSF function
		rtw_write8(Adapter, REG_BCN_CTRL, rtw_read8(Adapter, REG_BCN_CTRL)&(~BIT(3)));
		// disable TSF update instead! May induce burst beacon TX
		//rtw_write8(Adapter, REG_BCN_CTRL, rtw_read8(Adapter, REG_BCN_CTRL)|BIT(4));
							
		rtw_write32(Adapter, REG_TSFTR, tsf);
		rtw_write32(Adapter, REG_TSFTR+4, tsf>>32);

		//enable related TSF function
		rtw_write8(Adapter, REG_BCN_CTRL, rtw_read8(Adapter, REG_BCN_CTRL)|BIT(3));
		//rtw_write8(Adapter, REG_BCN_CTRL, rtw_read8(Adapter, REG_BCN_CTRL)&(~BIT(4)));		
		
		// Update buddy port's TSF if it is SoftAP for beacon TX issue!
		if ( (pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE
			&& check_buddy_fwstate(Adapter, WIFI_AP_STATE)
		) { 
			//disable related TSF function
			rtw_write8(Adapter, REG_BCN_CTRL_1, rtw_read8(Adapter, REG_BCN_CTRL_1)&(~BIT(3)));
			// disable TSF update instead!
			//rtw_write8(Adapter, REG_BCN_CTRL, rtw_read8(Adapter, REG_BCN_CTRL_1)|BIT(4));

			rtw_write32(Adapter, REG_TSFTR1, tsf);
			rtw_write32(Adapter, REG_TSFTR1+4, tsf>>32);

			//enable related TSF function
			rtw_write8(Adapter, REG_BCN_CTRL_1, rtw_read8(Adapter, REG_BCN_CTRL_1)|BIT(3));
			//rtw_write8(Adapter, REG_BCN_CTRL, rtw_read8(Adapter, REG_BCN_CTRL_1)&(~BIT(4)));
		}		
#ifdef CONFIG_TSF_RESET_OFFLOAD
		// Update buddy port's TSF if it is SoftAP for beacon TX issue!
		if ( (pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE
			&& check_buddy_fwstate(Adapter, WIFI_AP_STATE) ) {
			if (reset_tsf(Adapter, IFACE_PORT1) == _FALSE)
				DBG_871X("ERROR! %s()-%d: Reset port1 TSF fail\n",
					__FUNCTION__, __LINE__);
		}
#endif	// CONFIG_TSF_RESET_OFFLOAD
	}

	if(((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE))
	{
		//pHalData->RegTxPause  &= (~STOP_BCNQ);
		//rtw_write8(Adapter, REG_TXPAUSE, (rtw_read8(Adapter, REG_TXPAUSE)&(~BIT(6))));
		ResumeTxBeacon(Adapter);
	}
#endif	// CONFIG_CONCURRENT_MODE
}