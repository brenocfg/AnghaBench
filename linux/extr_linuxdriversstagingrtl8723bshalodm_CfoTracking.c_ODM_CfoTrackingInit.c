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
struct TYPE_7__ {int bAdjust; int /*<<< orphan*/  DefXCap; int /*<<< orphan*/  bATCStatus; int /*<<< orphan*/  CrystalCap; } ;
struct TYPE_6__ {TYPE_2__ DM_CfoTrack; } ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  TYPE_2__* PCFO_TRACKING ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CFO_TRACKING ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_GetATCStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_GetDefaultCrytaltalCap (TYPE_1__*) ; 

void ODM_CfoTrackingInit(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	PCFO_TRACKING pCfoTrack = &pDM_Odm->DM_CfoTrack;

	pCfoTrack->DefXCap =
		pCfoTrack->CrystalCap = odm_GetDefaultCrytaltalCap(pDM_Odm);
	pCfoTrack->bATCStatus = odm_GetATCStatus(pDM_Odm);
	pCfoTrack->bAdjust = true;
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CFO_TRACKING,
		ODM_DBG_LOUD,
		("ODM_CfoTracking_init() =========>\n")
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CFO_TRACKING,
		ODM_DBG_LOUD,
		(
			"ODM_CfoTracking_init(): bATCStatus = %d, CrystalCap = 0x%x\n",
			pCfoTrack->bATCStatus,
			pCfoTrack->DefXCap
		)
	);
}