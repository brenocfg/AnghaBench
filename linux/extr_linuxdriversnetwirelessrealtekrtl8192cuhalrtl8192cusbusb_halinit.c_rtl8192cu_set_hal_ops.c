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
struct hal_ops {int /*<<< orphan*/ * interface_ps_func; int /*<<< orphan*/ * hal_xmitframe_enqueue; int /*<<< orphan*/ * mgnt_xmit; int /*<<< orphan*/ * hal_xmit; int /*<<< orphan*/ * SetBeaconRelatedRegistersHandler; int /*<<< orphan*/ * UpdateRAMaskHandler; int /*<<< orphan*/ * SetHalDefVarHandler; int /*<<< orphan*/ * GetHalDefVarHandler; int /*<<< orphan*/ * GetHwRegHandler; int /*<<< orphan*/ * SetHwRegHandler; int /*<<< orphan*/ * read_adapter_info; int /*<<< orphan*/ * intf_chip_configure; int /*<<< orphan*/ * init_default_value; int /*<<< orphan*/ * DeInitSwLeds; int /*<<< orphan*/ * InitSwLeds; int /*<<< orphan*/ * free_recv_priv; int /*<<< orphan*/ * init_recv_priv; int /*<<< orphan*/ * free_xmit_priv; int /*<<< orphan*/ * init_xmit_priv; int /*<<< orphan*/ * inirp_deinit; int /*<<< orphan*/ * inirp_init; int /*<<< orphan*/ * hal_deinit; int /*<<< orphan*/ * hal_init; } ;
struct TYPE_3__ {int hal_data_sz; int /*<<< orphan*/ * HalData; struct hal_ops HalFunc; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  HAL_DATA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 int /*<<< orphan*/  GetHalDefVar8192CUsb ; 
 int /*<<< orphan*/  GetHwReg8192CU ; 
 int /*<<< orphan*/  ReadAdapterInfo8192CU ; 
 int /*<<< orphan*/  SetBeaconRelatedRegisters8192CUsb ; 
 int /*<<< orphan*/  SetHalDefVar8192CUsb ; 
 int /*<<< orphan*/  SetHwReg8192CU ; 
 int /*<<< orphan*/  UpdateHalRAMask8192CUsb ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtl8192c_set_hal_ops (struct hal_ops*) ; 
 int /*<<< orphan*/  rtl8192cu_free_recv_priv ; 
 int /*<<< orphan*/  rtl8192cu_free_xmit_priv ; 
 int /*<<< orphan*/  rtl8192cu_hal_deinit ; 
 int /*<<< orphan*/  rtl8192cu_hal_init ; 
 int /*<<< orphan*/  rtl8192cu_hal_xmit ; 
 int /*<<< orphan*/  rtl8192cu_hal_xmitframe_enqueue ; 
 int /*<<< orphan*/  rtl8192cu_inirp_deinit ; 
 int /*<<< orphan*/  rtl8192cu_inirp_init ; 
 int /*<<< orphan*/  rtl8192cu_init_default_value ; 
 int /*<<< orphan*/  rtl8192cu_init_recv_priv ; 
 int /*<<< orphan*/  rtl8192cu_init_xmit_priv ; 
 int /*<<< orphan*/  rtl8192cu_interface_configure ; 
 int /*<<< orphan*/  rtl8192cu_mgnt_xmit ; 
 int /*<<< orphan*/  rtl8192cu_ps_func ; 
 int /*<<< orphan*/ * rtw_zmalloc (int) ; 

void rtl8192cu_set_hal_ops(_adapter * padapter)
{
	struct hal_ops	*pHalFunc = &padapter->HalFunc;

_func_enter_;

	padapter->HalData = rtw_zmalloc(sizeof(HAL_DATA_TYPE));
	if(padapter->HalData == NULL){
		DBG_8192C("cant not alloc memory for HAL DATA \n");
	}
	//_rtw_memset(padapter->HalData, 0, sizeof(HAL_DATA_TYPE));
	padapter->hal_data_sz = sizeof(HAL_DATA_TYPE);

	pHalFunc->hal_init = &rtl8192cu_hal_init;
	pHalFunc->hal_deinit = &rtl8192cu_hal_deinit;

	//pHalFunc->free_hal_data = &rtl8192c_free_hal_data;

	pHalFunc->inirp_init = &rtl8192cu_inirp_init;
	pHalFunc->inirp_deinit = &rtl8192cu_inirp_deinit;

	pHalFunc->init_xmit_priv = &rtl8192cu_init_xmit_priv;
	pHalFunc->free_xmit_priv = &rtl8192cu_free_xmit_priv;

	pHalFunc->init_recv_priv = &rtl8192cu_init_recv_priv;
	pHalFunc->free_recv_priv = &rtl8192cu_free_recv_priv;
#ifdef CONFIG_SW_LED
	pHalFunc->InitSwLeds = &rtl8192cu_InitSwLeds;
	pHalFunc->DeInitSwLeds = &rtl8192cu_DeInitSwLeds;
#else //case of hw led or no led
	pHalFunc->InitSwLeds = NULL;
	pHalFunc->DeInitSwLeds = NULL;	
#endif//CONFIG_SW_LED

	//pHalFunc->dm_init = &rtl8192c_init_dm_priv;
	//pHalFunc->dm_deinit = &rtl8192c_deinit_dm_priv;

	pHalFunc->init_default_value = &rtl8192cu_init_default_value;
	pHalFunc->intf_chip_configure = &rtl8192cu_interface_configure;
	pHalFunc->read_adapter_info = &ReadAdapterInfo8192CU;

	//pHalFunc->set_bwmode_handler = &PHY_SetBWMode8192C;
	//pHalFunc->set_channel_handler = &PHY_SwChnl8192C;

	//pHalFunc->hal_dm_watchdog = &rtl8192c_HalDmWatchDog;

	pHalFunc->SetHwRegHandler = &SetHwReg8192CU;
	pHalFunc->GetHwRegHandler = &GetHwReg8192CU;
  	pHalFunc->GetHalDefVarHandler = &GetHalDefVar8192CUsb;
 	pHalFunc->SetHalDefVarHandler = &SetHalDefVar8192CUsb;

	pHalFunc->UpdateRAMaskHandler = &UpdateHalRAMask8192CUsb;
	pHalFunc->SetBeaconRelatedRegistersHandler = &SetBeaconRelatedRegisters8192CUsb;

	//pHalFunc->Add_RateATid = &rtl8192c_Add_RateATid;

//#ifdef CONFIG_SW_ANTENNA_DIVERSITY
	//pHalFunc->AntDivBeforeLinkHandler = &SwAntDivBeforeLink8192C;
	//pHalFunc->AntDivCompareHandler = &SwAntDivCompare8192C;
//#endif

	pHalFunc->hal_xmit = &rtl8192cu_hal_xmit;
	pHalFunc->mgnt_xmit = &rtl8192cu_mgnt_xmit;
	pHalFunc->hal_xmitframe_enqueue = &rtl8192cu_hal_xmitframe_enqueue;

	//pHalFunc->read_bbreg = &rtl8192c_PHY_QueryBBReg;
	//pHalFunc->write_bbreg = &rtl8192c_PHY_SetBBReg;
	//pHalFunc->read_rfreg = &rtl8192c_PHY_QueryRFReg;
	//pHalFunc->write_rfreg = &rtl8192c_PHY_SetRFReg;

#ifdef CONFIG_HOSTAPD_MLME
	pHalFunc->hostap_mgnt_xmit_entry = &rtl8192cu_hostap_mgnt_xmit_entry;
#endif
	pHalFunc->interface_ps_func = &rtl8192cu_ps_func;

	rtl8192c_set_hal_ops(pHalFunc);
_func_exit_;

}