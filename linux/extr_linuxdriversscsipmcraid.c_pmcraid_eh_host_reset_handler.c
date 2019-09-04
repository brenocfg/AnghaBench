#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct pmcraid_instance {TYPE_3__* pdev; int /*<<< orphan*/  outstanding_cmds; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int FAILED ; 
 scalar_t__ PMCRAID_MAX_HCAM_CMD ; 
 int /*<<< orphan*/  PMCRAID_RESET_HOST_TIMEOUT ; 
 int SUCCESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned long) ; 
 scalar_t__ pmcraid_reset_bringup (struct pmcraid_instance*) ; 

__attribute__((used)) static int pmcraid_eh_host_reset_handler(struct scsi_cmnd *scmd)
{
	unsigned long interval = 10000; /* 10 seconds interval */
	int waits = jiffies_to_msecs(PMCRAID_RESET_HOST_TIMEOUT) / interval;
	struct pmcraid_instance *pinstance =
		(struct pmcraid_instance *)(scmd->device->host->hostdata);


	/* wait for an additional 150 seconds just in case firmware could come
	 * up and if it could complete all the pending commands excluding the
	 * two HCAM (CCN and LDN).
	 */
	while (waits--) {
		if (atomic_read(&pinstance->outstanding_cmds) <=
		    PMCRAID_MAX_HCAM_CMD)
			return SUCCESS;
		msleep(interval);
	}

	dev_err(&pinstance->pdev->dev,
		"Adapter being reset due to an I/O command timeout.\n");
	return pmcraid_reset_bringup(pinstance) == 0 ? SUCCESS : FAILED;
}