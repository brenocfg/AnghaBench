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
struct TYPE_2__ {int bLinked; } ;
struct dm_priv {scalar_t__ EntryMinUndecoratedSmoothedPWDB; scalar_t__ MinUndecoratedPWDBForDM; } ;
struct hal_com_data {TYPE_1__ odmpriv; struct dm_priv dmpriv; } ;
struct adapter {int dummy; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 

__attribute__((used)) static void FindMinimumRSSI(struct adapter *padapter)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	struct dm_priv *pdmpriv = &pHalData->dmpriv;
	PDM_ODM_T pDM_Odm = &(pHalData->odmpriv);

	/* 1 1.Determine the minimum RSSI */

	if (
		(pDM_Odm->bLinked != true) &&
		(pdmpriv->EntryMinUndecoratedSmoothedPWDB == 0)
	) {
		pdmpriv->MinUndecoratedPWDBForDM = 0;
		/* ODM_RT_TRACE(pDM_Odm, COMP_BB_POWERSAVING, DBG_LOUD, ("Not connected to any\n")); */
	} else
		pdmpriv->MinUndecoratedPWDBForDM = pdmpriv->EntryMinUndecoratedSmoothedPWDB;

	/* DBG_8192C("%s =>MinUndecoratedPWDBForDM(%d)\n", __func__, pdmpriv->MinUndecoratedPWDBForDM); */
	/* ODM_RT_TRACE(pDM_Odm, COMP_DIG, DBG_LOUD, ("MinUndecoratedPWDBForDM =%d\n", pHalData->MinUndecoratedPWDBForDM)); */
}