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
typedef  scalar_t__ u8 ;
typedef  TYPE_1__* pDIG_T ;
struct TYPE_6__ {scalar_t__ CurIGValue; scalar_t__ rx_gain_range_max; int /*<<< orphan*/  bPSDInProgress; scalar_t__ bStopDIG; } ;
struct TYPE_7__ {scalar_t__ RFType; int /*<<< orphan*/  Adapter; TYPE_1__ DM_DigTable; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  IGI ; 
 int /*<<< orphan*/  IGI_A ; 
 int /*<<< orphan*/  IGI_B ; 
 scalar_t__ ODM_1T1R ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void ODM_Write_DIG(void *pDM_VOID, u8 CurrentIGI)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	pDIG_T pDM_DigTable = &pDM_Odm->DM_DigTable;

	if (pDM_DigTable->bStopDIG) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("Stop Writing IGI\n"));
		return;
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_TRACE, ("ODM_REG(IGI_A, pDM_Odm) = 0x%x, ODM_BIT(IGI, pDM_Odm) = 0x%x\n",
		ODM_REG(IGI_A, pDM_Odm), ODM_BIT(IGI, pDM_Odm)));

	if (pDM_DigTable->CurIGValue != CurrentIGI) {
		/* 1 Check initial gain by upper bound */
		if (!pDM_DigTable->bPSDInProgress) {
			if (CurrentIGI > pDM_DigTable->rx_gain_range_max) {
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_TRACE, ("CurrentIGI(0x%02x) is larger than upper bound !!\n", pDM_DigTable->rx_gain_range_max));
				CurrentIGI = pDM_DigTable->rx_gain_range_max;
			}

		}

		/* 1 Set IGI value */
		PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG(IGI_A, pDM_Odm), ODM_BIT(IGI, pDM_Odm), CurrentIGI);

		if (pDM_Odm->RFType > ODM_1T1R)
			PHY_SetBBReg(pDM_Odm->Adapter, ODM_REG(IGI_B, pDM_Odm), ODM_BIT(IGI, pDM_Odm), CurrentIGI);

		pDM_DigTable->CurIGValue = CurrentIGI;
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_TRACE, ("CurrentIGI(0x%02x).\n", CurrentIGI));

}