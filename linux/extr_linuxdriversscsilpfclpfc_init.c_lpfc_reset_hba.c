#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sli_flag; } ;
struct lpfc_hba {TYPE_1__ sli; int /*<<< orphan*/  link_state; int /*<<< orphan*/  cfg_enable_hba_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_MBX_NO_WAIT ; 
 int /*<<< orphan*/  LPFC_MBX_WAIT ; 
 int LPFC_SLI_ACTIVE ; 
 int /*<<< orphan*/  lpfc_offline (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_offline_prep (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_online (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 

void
lpfc_reset_hba(struct lpfc_hba *phba)
{
	/* If resets are disabled then set error state and return. */
	if (!phba->cfg_enable_hba_reset) {
		phba->link_state = LPFC_HBA_ERROR;
		return;
	}
	if (phba->sli.sli_flag & LPFC_SLI_ACTIVE)
		lpfc_offline_prep(phba, LPFC_MBX_WAIT);
	else
		lpfc_offline_prep(phba, LPFC_MBX_NO_WAIT);
	lpfc_offline(phba);
	lpfc_sli_brdrestart(phba);
	lpfc_online(phba);
	lpfc_unblock_mgmt_io(phba);
}