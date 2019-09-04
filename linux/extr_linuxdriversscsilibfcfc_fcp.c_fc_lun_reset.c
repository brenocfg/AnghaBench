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
struct fc_lport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fc_lun; int /*<<< orphan*/  fc_tm_flags; int /*<<< orphan*/  fc_dl; } ;
struct fc_fcp_pkt {int wait_for_comp; scalar_t__ cdb_status; int /*<<< orphan*/  scsi_pkt_lock; int /*<<< orphan*/ * seq_ptr; int /*<<< orphan*/  timer; int /*<<< orphan*/  state; int /*<<< orphan*/  tm_done; TYPE_1__ cdb_cmd; int /*<<< orphan*/  data_len; } ;

/* Variables and functions */
 int FAILED ; 
 scalar_t__ FCP_TMF_CMPL ; 
 int /*<<< orphan*/  FCP_TMF_LUN_RESET ; 
 int /*<<< orphan*/  FC_CMD_ABORTED ; 
 int /*<<< orphan*/  FC_SCSI_DBG (struct fc_lport*,char*,...) ; 
 int /*<<< orphan*/  FC_SCSI_TM_TOV ; 
 int /*<<< orphan*/  FC_SRB_COMPL ; 
 int SUCCESS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_exch_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_fcp_cleanup_each_cmd (struct fc_lport*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_lun_reset_send (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_to_scsilun (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_lun_reset(struct fc_lport *lport, struct fc_fcp_pkt *fsp,
			unsigned int id, unsigned int lun)
{
	int rc;

	fsp->cdb_cmd.fc_dl = htonl(fsp->data_len);
	fsp->cdb_cmd.fc_tm_flags = FCP_TMF_LUN_RESET;
	int_to_scsilun(lun, &fsp->cdb_cmd.fc_lun);

	fsp->wait_for_comp = 1;
	init_completion(&fsp->tm_done);

	fc_lun_reset_send(&fsp->timer);

	/*
	 * wait for completion of reset
	 * after that make sure all commands are terminated
	 */
	rc = wait_for_completion_timeout(&fsp->tm_done, FC_SCSI_TM_TOV);

	spin_lock_bh(&fsp->scsi_pkt_lock);
	fsp->state |= FC_SRB_COMPL;
	spin_unlock_bh(&fsp->scsi_pkt_lock);

	del_timer_sync(&fsp->timer);

	spin_lock_bh(&fsp->scsi_pkt_lock);
	if (fsp->seq_ptr) {
		fc_exch_done(fsp->seq_ptr);
		fsp->seq_ptr = NULL;
	}
	fsp->wait_for_comp = 0;
	spin_unlock_bh(&fsp->scsi_pkt_lock);

	if (!rc) {
		FC_SCSI_DBG(lport, "lun reset failed\n");
		return FAILED;
	}

	/* cdb_status holds the tmf's rsp code */
	if (fsp->cdb_status != FCP_TMF_CMPL)
		return FAILED;

	FC_SCSI_DBG(lport, "lun reset to lun %u completed\n", lun);
	fc_fcp_cleanup_each_cmd(lport, id, lun, FC_CMD_ABORTED);
	return SUCCESS;
}