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
typedef  int u8 ;
struct hal_com_data {int CrystalCap; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {struct adapter* Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 

__attribute__((used)) static u8 odm_GetDefaultCrytaltalCap(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	u8 CrystalCap = 0x20;

	struct adapter *Adapter = pDM_Odm->Adapter;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	CrystalCap = pHalData->CrystalCap;

	CrystalCap = CrystalCap & 0x3f;

	return CrystalCap;
}