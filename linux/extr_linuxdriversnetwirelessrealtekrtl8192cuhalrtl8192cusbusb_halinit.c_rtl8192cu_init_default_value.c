#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct pwrctrl_priv {int /*<<< orphan*/  bkeepfwalive; } ;
struct dm_priv {int prv_traffic_idx; scalar_t__* ThermalValue_HP; scalar_t__ ThermalValue_HP_index; scalar_t__ initialize; void* binitialized; scalar_t__ TM_Trigger; } ;
struct TYPE_6__ {struct pwrctrl_priv pwrctrlpriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_7__ {void* bIQKInitialized; scalar_t__ LastHMEBoxNum; void* fw_ractrl; struct dm_priv dmpriv; } ;
typedef  TYPE_2__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_2__* GET_HAL_DATA (TYPE_1__*) ; 
 size_t HP_THERMAL_NUM ; 
 void* _FALSE ; 

__attribute__((used)) static void rtl8192cu_init_default_value(_adapter * padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;
	struct dm_priv	*pdmpriv = &pHalData->dmpriv;
	u8	i;

	//init default value
	pHalData->fw_ractrl = _FALSE;	
	pHalData->bIQKInitialized = _FALSE;
	if(!pwrctrlpriv->bkeepfwalive)
		pHalData->LastHMEBoxNum = 0;
	
	pHalData->bIQKInitialized = _FALSE;
	//init dm default value
	pdmpriv->TM_Trigger = 0;
	pdmpriv->binitialized = _FALSE;
	pdmpriv->prv_traffic_idx = 3;
	pdmpriv->initialize = 0;

	pdmpriv->ThermalValue_HP_index = 0;
	for(i = 0; i < HP_THERMAL_NUM; i++)
		pdmpriv->ThermalValue_HP[i] = 0;
}