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
typedef  int u8 ;
struct vmscsi_request {int srb_status; int /*<<< orphan*/  target_id; int /*<<< orphan*/  lun; } ;
struct storvsc_scan_work {int /*<<< orphan*/  work; int /*<<< orphan*/  tgt_id; int /*<<< orphan*/  lun; struct Scsi_Host* host; } ;
struct scsi_cmnd {int /*<<< orphan*/ * cmnd; } ;
struct hv_host_device {int /*<<< orphan*/  handle_error_wq; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
#define  ATA_12 133 
#define  ATA_16 132 
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  DID_PASSTHROUGH ; 
 int /*<<< orphan*/  DID_REQUEUE ; 
 int /*<<< orphan*/  DID_TARGET_FAILURE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 int SRB_STATUS (int) ; 
#define  SRB_STATUS_ABORTED 131 
 int SRB_STATUS_AUTOSENSE_VALID ; 
#define  SRB_STATUS_ERROR 130 
#define  SRB_STATUS_INVALID_LUN 129 
#define  TEST_UNIT_READY 128 
 struct storvsc_scan_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 struct hv_host_device* shost_priv (struct Scsi_Host*) ; 
 void storvsc_device_scan (struct work_struct*) ; 
 void storvsc_remove_lun (struct work_struct*) ; 

__attribute__((used)) static void storvsc_handle_error(struct vmscsi_request *vm_srb,
				struct scsi_cmnd *scmnd,
				struct Scsi_Host *host,
				u8 asc, u8 ascq)
{
	struct storvsc_scan_work *wrk;
	void (*process_err_fn)(struct work_struct *work);
	struct hv_host_device *host_dev = shost_priv(host);
	bool do_work = false;

	switch (SRB_STATUS(vm_srb->srb_status)) {
	case SRB_STATUS_ERROR:
		/*
		 * Let upper layer deal with error when
		 * sense message is present.
		 */

		if (vm_srb->srb_status & SRB_STATUS_AUTOSENSE_VALID)
			break;
		/*
		 * If there is an error; offline the device since all
		 * error recovery strategies would have already been
		 * deployed on the host side. However, if the command
		 * were a pass-through command deal with it appropriately.
		 */
		switch (scmnd->cmnd[0]) {
		case ATA_16:
		case ATA_12:
			set_host_byte(scmnd, DID_PASSTHROUGH);
			break;
		/*
		 * On Some Windows hosts TEST_UNIT_READY command can return
		 * SRB_STATUS_ERROR, let the upper level code deal with it
		 * based on the sense information.
		 */
		case TEST_UNIT_READY:
			break;
		default:
			set_host_byte(scmnd, DID_ERROR);
		}
		break;
	case SRB_STATUS_INVALID_LUN:
		set_host_byte(scmnd, DID_NO_CONNECT);
		do_work = true;
		process_err_fn = storvsc_remove_lun;
		break;
	case SRB_STATUS_ABORTED:
		if (vm_srb->srb_status & SRB_STATUS_AUTOSENSE_VALID &&
		    (asc == 0x2a) && (ascq == 0x9)) {
			do_work = true;
			process_err_fn = storvsc_device_scan;
			/*
			 * Retry the I/O that trigerred this.
			 */
			set_host_byte(scmnd, DID_REQUEUE);
		}
		break;
	}

	if (!do_work)
		return;

	/*
	 * We need to schedule work to process this error; schedule it.
	 */
	wrk = kmalloc(sizeof(struct storvsc_scan_work), GFP_ATOMIC);
	if (!wrk) {
		set_host_byte(scmnd, DID_TARGET_FAILURE);
		return;
	}

	wrk->host = host;
	wrk->lun = vm_srb->lun;
	wrk->tgt_id = vm_srb->target_id;
	INIT_WORK(&wrk->work, process_err_fn);
	queue_work(host_dev->handle_error_wq, &wrk->work);
}