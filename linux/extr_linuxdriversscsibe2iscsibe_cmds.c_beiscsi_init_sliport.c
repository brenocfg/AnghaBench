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
struct beiscsi_hba {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_IN_ERR ; 
 int /*<<< orphan*/  BEISCSI_HBA_UER_SUPP ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int beiscsi_check_fw_rdy (struct beiscsi_hba*) ; 
 int beiscsi_cmd_function_reset (struct beiscsi_hba*) ; 
 int beiscsi_cmd_special_wrb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int beiscsi_init_sliport(struct beiscsi_hba *phba)
{
	int status;

	/* check POST stage before talking to FW */
	status = beiscsi_check_fw_rdy(phba);
	if (!status)
		return -EIO;

	/* clear all error states after checking FW rdy */
	phba->state &= ~BEISCSI_HBA_IN_ERR;

	/* check again UER support */
	phba->state &= ~BEISCSI_HBA_UER_SUPP;

	/*
	 * SLI COMMON_FUNCTION_RESET completion is indicated by BMBX RDY bit.
	 * It should clean up any stale info in FW for this fn.
	 */
	status = beiscsi_cmd_function_reset(phba);
	if (status) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BC_%d : SLI Function Reset failed\n");
		return status;
	}

	/* indicate driver is loading */
	return beiscsi_cmd_special_wrb(&phba->ctrl, 1);
}