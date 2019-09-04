#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct odm_dm_struct {struct adapter* Adapter; } ;
struct dm_priv {int bDynamicTxPowerEnable; void* DynamicTxHighPowerLvl; void* LastDTPLvl; } ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {struct dm_priv dmpriv; } ;

/* Variables and functions */
 void* TxHighPwrLevel_Normal ; 

void odm_DynamicTxPowerInit(struct odm_dm_struct *pDM_Odm)
{
	struct adapter *Adapter = pDM_Odm->Adapter;
	struct dm_priv	*pdmpriv = &Adapter->HalData->dmpriv;

	pdmpriv->bDynamicTxPowerEnable = false;
	pdmpriv->LastDTPLvl = TxHighPwrLevel_Normal;
	pdmpriv->DynamicTxHighPowerLvl = TxHighPwrLevel_Normal;
}