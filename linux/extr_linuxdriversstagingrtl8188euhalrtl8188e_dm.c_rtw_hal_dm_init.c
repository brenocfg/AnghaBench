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
struct dm_priv {int dummy; } ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {struct odm_dm_struct odmpriv; struct dm_priv dmpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  Init_ODM_ComInfo_88E (struct adapter*) ; 
 int /*<<< orphan*/  ODM_InitDebugSetting (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  memset (struct dm_priv*,int /*<<< orphan*/ ,int) ; 

void rtw_hal_dm_init(struct adapter *Adapter)
{
	struct dm_priv	*pdmpriv = &Adapter->HalData->dmpriv;
	struct odm_dm_struct *podmpriv = &Adapter->HalData->odmpriv;

	memset(pdmpriv, 0, sizeof(struct dm_priv));
	Init_ODM_ComInfo_88E(Adapter);
	ODM_InitDebugSetting(podmpriv);
}