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
struct odm_dm_struct {int dummy; } ;
struct dm_priv {int /*<<< orphan*/  DMFlag; int /*<<< orphan*/  DM_Type; } ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {struct odm_dm_struct odmpriv; struct dm_priv dmpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_Type_ByDriver ; 
 int /*<<< orphan*/  DYNAMIC_FUNC_DISABLE ; 
 int /*<<< orphan*/  ODM_DMInit (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  Update_ODM_ComInfo_88E (struct adapter*) ; 
 int /*<<< orphan*/  dm_InitGPIOSetting (struct adapter*) ; 

void rtl8188e_InitHalDm(struct adapter *Adapter)
{
	struct dm_priv	*pdmpriv = &Adapter->HalData->dmpriv;
	struct odm_dm_struct *dm_odm = &(Adapter->HalData->odmpriv);

	dm_InitGPIOSetting(Adapter);
	pdmpriv->DM_Type = DM_Type_ByDriver;
	pdmpriv->DMFlag = DYNAMIC_FUNC_DISABLE;
	Update_ODM_ComInfo_88E(Adapter);
	ODM_DMInit(dm_odm);
}