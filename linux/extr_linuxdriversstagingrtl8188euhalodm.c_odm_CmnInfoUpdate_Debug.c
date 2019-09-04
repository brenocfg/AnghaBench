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
struct odm_dm_struct {int /*<<< orphan*/  RSSI_Min; int /*<<< orphan*/  bLinked; int /*<<< orphan*/  bWIFI_Display; int /*<<< orphan*/  bWIFI_Direct; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_COMMON ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void odm_CmnInfoUpdate_Debug(struct odm_dm_struct *pDM_Odm)
{
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("odm_CmnInfoUpdate_Debug==>\n"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bWIFI_Direct=%d\n", pDM_Odm->bWIFI_Direct));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bWIFI_Display=%d\n", pDM_Odm->bWIFI_Display));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("bLinked=%d\n", pDM_Odm->bLinked));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("RSSI_Min=%d\n", pDM_Odm->RSSI_Min));
}