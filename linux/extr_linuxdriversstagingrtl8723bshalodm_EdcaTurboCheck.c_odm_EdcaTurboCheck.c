#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int SupportAbility; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_EDCA_TURBO ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int ODM_MAC_EDCA_TURBO ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_EdcaTurboCheckCE (TYPE_1__*) ; 

void odm_EdcaTurboCheck(void *pDM_VOID)
{
	/*  In HW integration first stage, we provide 4 different handles to
	 *  operate at the same time. In stage2/3, we need to prove universal
	 *  interface and merge all HW dynamic mechanism.
	 */
	PDM_ODM_T		pDM_Odm = (PDM_ODM_T)pDM_VOID;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("odm_EdcaTurboCheck ========================>\n"));

	if (!(pDM_Odm->SupportAbility & ODM_MAC_EDCA_TURBO))
		return;

	odm_EdcaTurboCheckCE(pDM_Odm);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("<========================odm_EdcaTurboCheck\n"));
}