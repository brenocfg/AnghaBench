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
struct TYPE_7__ {int bAdjust; int /*<<< orphan*/  DefXCap; } ;
struct TYPE_6__ {TYPE_2__ DM_CfoTrack; } ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  TYPE_2__* PCFO_TRACKING ;

/* Variables and functions */
 int /*<<< orphan*/  odm_GetDefaultCrytaltalCap (TYPE_1__*) ; 
 int /*<<< orphan*/  odm_SetATCStatus (TYPE_1__*,int) ; 
 int /*<<< orphan*/  odm_SetCrystalCap (TYPE_1__*,int /*<<< orphan*/ ) ; 

void ODM_CfoTrackingReset(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	PCFO_TRACKING pCfoTrack = &pDM_Odm->DM_CfoTrack;

	pCfoTrack->DefXCap = odm_GetDefaultCrytaltalCap(pDM_Odm);
	pCfoTrack->bAdjust = true;

	odm_SetCrystalCap(pDM_Odm, pCfoTrack->DefXCap);
	odm_SetATCStatus(pDM_Odm, true);
}