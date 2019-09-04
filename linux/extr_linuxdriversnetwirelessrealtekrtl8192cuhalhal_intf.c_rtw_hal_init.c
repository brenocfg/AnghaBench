#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
struct TYPE_15__ {int notch_filter; } ;
struct TYPE_14__ {scalar_t__ (* hal_init ) (TYPE_3__*) ;} ;
struct TYPE_16__ {scalar_t__ hw_init_completed; TYPE_2__ registrypriv; TYPE_1__ HalFunc; struct TYPE_16__* pbuddy_adapter; } ;
typedef  TYPE_3__ _adapter ;
struct TYPE_13__ {scalar_t__ DualMacMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 TYPE_11__* adapter_to_dvobj (TYPE_3__*) ; 
 int /*<<< orphan*/  init_hw_mlme_ext (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_hal_notch_filter (TYPE_3__*,int) ; 
 int /*<<< orphan*/  rtw_hal_reset_security_engine (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_sec_restore_wep_key (TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
 scalar_t__ stub2 (TYPE_3__*) ; 

uint	 rtw_hal_init(_adapter *padapter) 
{
	uint	status = _SUCCESS;

	if(padapter->hw_init_completed == _TRUE)
	{
		DBG_871X("rtw_hal_init: hw_init_completed == _TRUE\n");
		goto success;
	}
#ifdef CONFIG_DEINIT_BEFORE_INIT
	status = padapter->HalFunc.hal_deinit(padapter);
	if(status != _SUCCESS){
		DBG_871X("rtw_hal_init: hal_deinit before hal_init FAIL !!\n");
		goto fail;
	}
#endif
	
#ifdef CONFIG_DUALMAC_CONCURRENT
	// before init mac0, driver must init mac1 first to avoid usb rx error.
	if((padapter->pbuddy_adapter != NULL) && (padapter->DualMacConcurrent == _TRUE)
		&& (padapter->adapter_type == PRIMARY_ADAPTER))
	{
		if(padapter->pbuddy_adapter->hw_init_completed == _TRUE)
		{
			DBG_871X("rtw_hal_init: pbuddy_adapter hw_init_completed == _TRUE\n");
		}
		else
		{
#ifdef CONFIG_DEINIT_BEFORE_INIT
			status = padapter->HalFunc.hal_deinit(padapter->pbuddy_adapter);
			if(status != _SUCCESS){
				DBG_871X("rtw_hal_init: hal_deinit before hal_init FAIL !!(pbuddy_adapter)\n");
				goto fail;
			}
#endif
			status = 	padapter->HalFunc.hal_init(padapter->pbuddy_adapter);
			if(status == _SUCCESS){
				padapter->pbuddy_adapter->hw_init_completed = _TRUE;
			}
			else{
			 	padapter->pbuddy_adapter->hw_init_completed = _FALSE;
				RT_TRACE(_module_hal_init_c_,_drv_err_,("rtw_hal_init: hal__init fail(pbuddy_adapter)\n"));
				goto fail;
			}
		}
	}
#else
	if(adapter_to_dvobj(padapter)->DualMacMode == _TRUE)
	{
		if(padapter->pbuddy_adapter != NULL) {
			if(padapter->pbuddy_adapter->hw_init_completed == _FALSE)
			{
#ifdef CONFIG_DEINIT_BEFORE_INIT
				status = padapter->HalFunc.hal_deinit(padapter->pbuddy_adapter);
				if(status != _SUCCESS){
					DBG_871X("rtw_hal_init: hal_deinit before hal_init FAIL !!(pbuddy_adapter)\n");
					goto fail;
				}
#endif
				status = padapter->HalFunc.hal_init(padapter->pbuddy_adapter);
				if(status == _SUCCESS){
					padapter->pbuddy_adapter->hw_init_completed = _TRUE;
				}
				else{
					padapter->pbuddy_adapter->hw_init_completed = _FALSE;
					RT_TRACE(_module_hal_init_c_,_drv_err_,("rtw_hal_init: hal__init fail for another interface\n"));
				}
			}
		}
	}
#endif

	padapter->hw_init_completed=_FALSE;

	status = padapter->HalFunc.hal_init(padapter);

	if(status == _SUCCESS){
		padapter->hw_init_completed = _TRUE;
	}
	else{
	 	padapter->hw_init_completed = _FALSE;
		RT_TRACE(_module_hal_init_c_,_drv_err_,("rtw_hal_init: hal__init fail\n"));
		goto fail;
	}

success:

	if (padapter->registrypriv.notch_filter == 1)
		rtw_hal_notch_filter(padapter, 1);

	rtw_hal_reset_security_engine(padapter);

	rtw_sec_restore_wep_key(padapter);

	init_hw_mlme_ext(padapter);

fail:

	RT_TRACE(_module_hal_init_c_,_drv_err_,("-rtl871x_hal_init:status=0x%x\n",status));

	return status;
}