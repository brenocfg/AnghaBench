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
struct TYPE_3__ {int Carrier_Sense_enable; int TH_L2H_ini; int AdapEn_RSSI; int TH_EDCCA_HL_diff; int IGI_Base; int IGI_target; int NHM_disable; int TxHangFlg; int /*<<< orphan*/  Adapter; scalar_t__ Adaptivity_IGI_upper; scalar_t__ L2H_lb; scalar_t__ H2L_lb; scalar_t__ txEdcca1; scalar_t__ txEdcca0; scalar_t__ ForceEDCCA; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  BIT11 ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_RD_CTRL ; 
 int /*<<< orphan*/  odm_NHMBBInit (TYPE_1__*) ; 

void odm_AdaptivityInit(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;

	if (pDM_Odm->Carrier_Sense_enable == false)
		pDM_Odm->TH_L2H_ini = 0xf7; /*  -7 */
	else
		pDM_Odm->TH_L2H_ini = 0xa;

	pDM_Odm->AdapEn_RSSI = 20;
	pDM_Odm->TH_EDCCA_HL_diff = 7;

	pDM_Odm->IGI_Base = 0x32;
	pDM_Odm->IGI_target = 0x1c;
	pDM_Odm->ForceEDCCA = 0;
	pDM_Odm->NHM_disable = false;
	pDM_Odm->TxHangFlg = true;
	pDM_Odm->txEdcca0 = 0;
	pDM_Odm->txEdcca1 = 0;
	pDM_Odm->H2L_lb = 0;
	pDM_Odm->L2H_lb = 0;
	pDM_Odm->Adaptivity_IGI_upper = 0;
	odm_NHMBBInit(pDM_Odm);

	PHY_SetBBReg(pDM_Odm->Adapter, REG_RD_CTRL, BIT11, 1); /*  stop counting if EDCCA is asserted */
}