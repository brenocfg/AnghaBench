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
struct odm_rate_adapt {scalar_t__ Type; int HighRSSIThresh; int LowRSSIThresh; int /*<<< orphan*/  RATRState; } ;
struct odm_dm_struct {int bUseRAMask; struct odm_rate_adapt RateAdaptive; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RATR_STA_INIT ; 
 scalar_t__ DM_Type_ByDriver ; 

void odm_RateAdaptiveMaskInit(struct odm_dm_struct *pDM_Odm)
{
	struct odm_rate_adapt *pOdmRA = &pDM_Odm->RateAdaptive;

	pOdmRA->Type = DM_Type_ByDriver;
	if (pOdmRA->Type == DM_Type_ByDriver)
		pDM_Odm->bUseRAMask = true;
	else
		pDM_Odm->bUseRAMask = false;

	pOdmRA->RATRState = DM_RATR_STA_INIT;
	pOdmRA->HighRSSIThresh = 50;
	pOdmRA->LowRSSIThresh = 20;
}