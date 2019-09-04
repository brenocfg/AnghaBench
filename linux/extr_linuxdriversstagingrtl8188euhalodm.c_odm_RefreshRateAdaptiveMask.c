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
struct odm_dm_struct {int SupportAbility; } ;

/* Variables and functions */
 int ODM_BB_RA_MASK ; 
 int /*<<< orphan*/  odm_RefreshRateAdaptiveMaskCE (struct odm_dm_struct*) ; 

void odm_RefreshRateAdaptiveMask(struct odm_dm_struct *pDM_Odm)
{
	if (!(pDM_Odm->SupportAbility & ODM_BB_RA_MASK))
		return;
	/*  */
	/*  2011/09/29 MH In HW integration first stage, we provide 4 different handle to operate */
	/*  at the same time. In the stage2/3, we need to prive universal interface and merge all */
	/*  HW dynamic mechanism. */
	/*  */
	odm_RefreshRateAdaptiveMaskCE(pDM_Odm);
}