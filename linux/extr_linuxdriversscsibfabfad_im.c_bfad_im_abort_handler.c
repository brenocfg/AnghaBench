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
typedef  int u32 ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;scalar_t__ host_scribble; TYPE_1__* device; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; } ;
struct bfad_ioim_s {int dummy; } ;
struct bfad_im_port_s {TYPE_2__* shost; struct bfad_s* bfad; } ;
struct bfa_ioim_s {int /*<<< orphan*/  iotag; struct bfad_ioim_s* dio; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int FAILED ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  bfa_ioim_abort (struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int
bfad_im_abort_handler(struct scsi_cmnd *cmnd)
{
	struct Scsi_Host *shost = cmnd->device->host;
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_s         *bfad = im_port->bfad;
	struct bfa_ioim_s *hal_io;
	unsigned long   flags;
	u32        timeout;
	int             rc = FAILED;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	hal_io = (struct bfa_ioim_s *) cmnd->host_scribble;
	if (!hal_io) {
		/* IO has been completed, return success */
		rc = SUCCESS;
		goto out;
	}
	if (hal_io->dio != (struct bfad_ioim_s *) cmnd) {
		rc = FAILED;
		goto out;
	}

	bfa_trc(bfad, hal_io->iotag);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"scsi%d: abort cmnd %p iotag %x\n",
		im_port->shost->host_no, cmnd, hal_io->iotag);
	(void) bfa_ioim_abort(hal_io);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	/* Need to wait until the command get aborted */
	timeout = 10;
	while ((struct bfa_ioim_s *) cmnd->host_scribble == hal_io) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(timeout);
		if (timeout < 4 * HZ)
			timeout *= 2;
	}

	cmnd->scsi_done(cmnd);
	bfa_trc(bfad, hal_io->iotag);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"scsi%d: complete abort 0x%p iotag 0x%x\n",
		im_port->shost->host_no, cmnd, hal_io->iotag);
	return SUCCESS;
out:
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	return rc;
}