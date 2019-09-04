#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtw_dig {int PreCCK_CCAThres; int CurCCK_CCAThres; int bMediaConnect_0; int bMediaConnect_1; void* DIG_Dynamic_MIN_1; void* DIG_Dynamic_MIN_0; scalar_t__ Recover_cnt; scalar_t__ LargeFAHit; void* ForbiddenIGI; int /*<<< orphan*/  BackoffVal_range_min; int /*<<< orphan*/  BackoffVal_range_max; int /*<<< orphan*/  BackoffVal; void* rx_gain_range_min; int /*<<< orphan*/  rx_gain_range_max; int /*<<< orphan*/  FAHighThresh; int /*<<< orphan*/  FALowThresh; int /*<<< orphan*/  RssiHighThresh; int /*<<< orphan*/  RssiLowThresh; scalar_t__ CurIGValue; } ;
struct odm_dm_struct {int bDMInitialGainEnable; struct rtw_dig DM_DigTable; struct adapter* Adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_DIG_BACKOFF_DEFAULT ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MAX ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MIN ; 
 int /*<<< orphan*/  DM_DIG_MAX_NIC ; 
 void* DM_DIG_MIN_NIC ; 
 int /*<<< orphan*/  DM_DIG_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_DIG_THRESH_LOW ; 
 int /*<<< orphan*/  DM_false_ALARM_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_false_ALARM_THRESH_LOW ; 
 int /*<<< orphan*/  ODM_BIT_IGI_11N ; 
 int /*<<< orphan*/  ODM_REG_IGI_A_11N ; 
 scalar_t__ phy_query_bb_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void odm_DIGInit(struct odm_dm_struct *pDM_Odm)
{
	struct adapter *adapter = pDM_Odm->Adapter;
	struct rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;

	pDM_DigTable->CurIGValue = (u8)phy_query_bb_reg(adapter, ODM_REG_IGI_A_11N, ODM_BIT_IGI_11N);
	pDM_DigTable->RssiLowThresh	= DM_DIG_THRESH_LOW;
	pDM_DigTable->RssiHighThresh	= DM_DIG_THRESH_HIGH;
	pDM_DigTable->FALowThresh	= DM_false_ALARM_THRESH_LOW;
	pDM_DigTable->FAHighThresh	= DM_false_ALARM_THRESH_HIGH;
	pDM_DigTable->rx_gain_range_max = DM_DIG_MAX_NIC;
	pDM_DigTable->rx_gain_range_min = DM_DIG_MIN_NIC;
	pDM_DigTable->BackoffVal = DM_DIG_BACKOFF_DEFAULT;
	pDM_DigTable->BackoffVal_range_max = DM_DIG_BACKOFF_MAX;
	pDM_DigTable->BackoffVal_range_min = DM_DIG_BACKOFF_MIN;
	pDM_DigTable->PreCCK_CCAThres = 0xFF;
	pDM_DigTable->CurCCK_CCAThres = 0x83;
	pDM_DigTable->ForbiddenIGI = DM_DIG_MIN_NIC;
	pDM_DigTable->LargeFAHit = 0;
	pDM_DigTable->Recover_cnt = 0;
	pDM_DigTable->DIG_Dynamic_MIN_0 = DM_DIG_MIN_NIC;
	pDM_DigTable->DIG_Dynamic_MIN_1 = DM_DIG_MIN_NIC;
	pDM_DigTable->bMediaConnect_0 = false;
	pDM_DigTable->bMediaConnect_1 = false;

	/* To Initialize pDM_Odm->bDMInitialGainEnable == false to avoid DIG error */
	pDM_Odm->bDMInitialGainEnable = true;
}