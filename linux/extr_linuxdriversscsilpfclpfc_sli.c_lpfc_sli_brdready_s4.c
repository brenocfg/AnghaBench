#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ intr_enable; } ;
struct lpfc_hba {TYPE_2__ sli4_hba; int /*<<< orphan*/  link_state; TYPE_1__* pport; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_VPORT_UNKNOWN ; 
 scalar_t__ lpfc_sli4_post_status_check (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 

__attribute__((used)) static int
lpfc_sli_brdready_s4(struct lpfc_hba *phba, uint32_t mask)
{
	uint32_t status;
	int retval = 0;

	/* Read the HBA Host Status Register */
	status = lpfc_sli4_post_status_check(phba);

	if (status) {
		phba->pport->port_state = LPFC_VPORT_UNKNOWN;
		lpfc_sli_brdrestart(phba);
		status = lpfc_sli4_post_status_check(phba);
	}

	/* Check to see if any errors occurred during init */
	if (status) {
		phba->link_state = LPFC_HBA_ERROR;
		retval = 1;
	} else
		phba->sli4_hba.intr_enable = 0;

	return retval;
}