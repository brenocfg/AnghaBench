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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct odm_ra_info {int* RTY; int DROP; int TOTAL; int RAstage; int RptTime; int /*<<< orphan*/  RateSGI; int /*<<< orphan*/  DecisionRate; scalar_t__ PTActive; } ;
struct odm_dm_struct {struct odm_ra_info* RAInfo; } ;

/* Variables and functions */
 int ASSOCIATE_ENTRY_NUM ; 
 scalar_t__ GET_TX_REPORT_TYPE1_DROP_0 (int*) ; 
 scalar_t__ GET_TX_REPORT_TYPE1_RERTY_0 (int*) ; 
 scalar_t__ GET_TX_REPORT_TYPE1_RERTY_1 (int*) ; 
 scalar_t__ GET_TX_REPORT_TYPE1_RERTY_2 (int*) ; 
 scalar_t__ GET_TX_REPORT_TYPE1_RERTY_3 (int*) ; 
 scalar_t__ GET_TX_REPORT_TYPE1_RERTY_4 (int*) ; 
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TX_RPT2_ITEM_SIZE ; 
 int /*<<< orphan*/  odm_PTDecision_8188E (struct odm_ra_info*) ; 
 int /*<<< orphan*/  odm_PTTryState_8188E (struct odm_ra_info*) ; 
 int /*<<< orphan*/  odm_RATxRPTTimerSetting (struct odm_dm_struct*,int) ; 
 int /*<<< orphan*/  odm_RateDecision_8188E (struct odm_dm_struct*,struct odm_ra_info*) ; 

void ODM_RA_TxRPT2Handle_8188E(struct odm_dm_struct *dm_odm, u8 *TxRPT_Buf, u16 TxRPT_Len, u32 macid_entry0, u32 macid_entry1)
{
	struct odm_ra_info *pRAInfo = NULL;
	u8 MacId = 0;
	u8 *pBuffer = NULL;
	u32 valid = 0, ItemNum = 0;
	u16 minRptTime = 0x927c;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("=====>ODM_RA_TxRPT2Handle_8188E(): valid0 =%d valid1 =%d BufferLength =%d\n",
		     macid_entry0, macid_entry1, TxRPT_Len));

	ItemNum = TxRPT_Len >> 3;
	pBuffer = TxRPT_Buf;

	do {
		if (MacId >= ASSOCIATE_ENTRY_NUM)
			valid = 0;
		else if (MacId >= 32)
			valid = (1 << (MacId - 32)) & macid_entry1;
		else
			valid = (1 << MacId) & macid_entry0;

		pRAInfo = &(dm_odm->RAInfo[MacId]);
		if (valid) {
			pRAInfo->RTY[0] = (u16)GET_TX_REPORT_TYPE1_RERTY_0(pBuffer);
			pRAInfo->RTY[1] = (u16)GET_TX_REPORT_TYPE1_RERTY_1(pBuffer);
			pRAInfo->RTY[2] = (u16)GET_TX_REPORT_TYPE1_RERTY_2(pBuffer);
			pRAInfo->RTY[3] = (u16)GET_TX_REPORT_TYPE1_RERTY_3(pBuffer);
			pRAInfo->RTY[4] = (u16)GET_TX_REPORT_TYPE1_RERTY_4(pBuffer);
			pRAInfo->DROP =   (u16)GET_TX_REPORT_TYPE1_DROP_0(pBuffer);
			pRAInfo->TOTAL = pRAInfo->RTY[0] + pRAInfo->RTY[1] +
					 pRAInfo->RTY[2] + pRAInfo->RTY[3] +
					 pRAInfo->RTY[4] + pRAInfo->DROP;
			if (pRAInfo->TOTAL != 0) {
				ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
					     ("macid =%d Total =%d R0 =%d R1 =%d R2 =%d R3 =%d R4 =%d D0 =%d valid0 =%x valid1 =%x\n",
					     MacId, pRAInfo->TOTAL,
					     pRAInfo->RTY[0], pRAInfo->RTY[1],
					     pRAInfo->RTY[2], pRAInfo->RTY[3],
					     pRAInfo->RTY[4], pRAInfo->DROP,
					     macid_entry0, macid_entry1));
				if (pRAInfo->PTActive) {
					if (pRAInfo->RAstage < 5)
						odm_RateDecision_8188E(dm_odm, pRAInfo);
					else if (pRAInfo->RAstage == 5) /*  Power training try state */
						odm_PTTryState_8188E(pRAInfo);
					else /*  RAstage == 6 */
						odm_PTDecision_8188E(pRAInfo);

					/*  Stage_RA counter */
					if (pRAInfo->RAstage <= 5)
						pRAInfo->RAstage++;
					else
						pRAInfo->RAstage = 0;
				} else {
					odm_RateDecision_8188E(dm_odm, pRAInfo);
				}
				ODM_RT_TRACE(dm_odm, ODM_COMP_INIT, ODM_DBG_LOUD,
					     ("macid =%d R0 =%d R1 =%d R2 =%d R3 =%d R4 =%d drop =%d valid0 =%x RateID =%d SGI =%d\n",
					     MacId,
					     pRAInfo->RTY[0],
					     pRAInfo->RTY[1],
					     pRAInfo->RTY[2],
					     pRAInfo->RTY[3],
					     pRAInfo->RTY[4],
					     pRAInfo->DROP,
					     macid_entry0,
					     pRAInfo->DecisionRate,
					     pRAInfo->RateSGI));
			} else {
				ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD, (" TOTAL = 0!!!!\n"));
			}
		}

		if (minRptTime > pRAInfo->RptTime)
			minRptTime = pRAInfo->RptTime;

		pBuffer += TX_RPT2_ITEM_SIZE;
		MacId++;
	} while (MacId < ItemNum);

	odm_RATxRPTTimerSetting(dm_odm, minRptTime);

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD, ("<===== ODM_RA_TxRPT2Handle_8188E()\n"));
}