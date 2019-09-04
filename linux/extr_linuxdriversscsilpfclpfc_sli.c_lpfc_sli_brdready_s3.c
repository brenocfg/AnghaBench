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
typedef  int uint32_t ;
struct lpfc_hba {int /*<<< orphan*/  link_state; scalar_t__ MBslimaddr; int /*<<< orphan*/  HSregaddr; TYPE_1__* pport; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_state; } ;

/* Variables and functions */
 int HS_FFERM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_HBA_ERROR ; 
 int /*<<< orphan*/  LPFC_VPORT_UNKNOWN ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_readl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int
lpfc_sli_brdready_s3(struct lpfc_hba *phba, uint32_t mask)
{
	uint32_t status;
	int i = 0;
	int retval = 0;

	/* Read the HBA Host Status Register */
	if (lpfc_readl(phba->HSregaddr, &status))
		return 1;

	/*
	 * Check status register every 100ms for 5 retries, then every
	 * 500ms for 5, then every 2.5 sec for 5, then reset board and
	 * every 2.5 sec for 4.
	 * Break our of the loop if errors occurred during init.
	 */
	while (((status & mask) != mask) &&
	       !(status & HS_FFERM) &&
	       i++ < 20) {

		if (i <= 5)
			msleep(10);
		else if (i <= 10)
			msleep(500);
		else
			msleep(2500);

		if (i == 15) {
				/* Do post */
			phba->pport->port_state = LPFC_VPORT_UNKNOWN;
			lpfc_sli_brdrestart(phba);
		}
		/* Read the HBA Host Status Register */
		if (lpfc_readl(phba->HSregaddr, &status)) {
			retval = 1;
			break;
		}
	}

	/* Check to see if any errors occurred during init */
	if ((status & HS_FFERM) || (i >= 20)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2751 Adapter failed to restart, "
				"status reg x%x, FW Data: A8 x%x AC x%x\n",
				status,
				readl(phba->MBslimaddr + 0xa8),
				readl(phba->MBslimaddr + 0xac));
		phba->link_state = LPFC_HBA_ERROR;
		retval = 1;
	}

	return retval;
}