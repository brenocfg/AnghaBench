#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bATCStatus; } ;
struct TYPE_5__ {int /*<<< orphan*/  Adapter; TYPE_2__ DM_CfoTrack; } ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  TYPE_2__* PCFO_TRACKING ;

/* Variables and functions */
 int /*<<< orphan*/  BB_ATC ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void odm_SetATCStatus(void *pDM_VOID, bool ATCStatus)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	PCFO_TRACKING pCfoTrack = &pDM_Odm->DM_CfoTrack;

	if (pCfoTrack->bATCStatus == ATCStatus)
		return;

	PHY_SetBBReg(
		pDM_Odm->Adapter,
		ODM_REG(BB_ATC, pDM_Odm),
		ODM_BIT(BB_ATC, pDM_Odm),
		ATCStatus
	);
	pCfoTrack->bATCStatus = ATCStatus;
}