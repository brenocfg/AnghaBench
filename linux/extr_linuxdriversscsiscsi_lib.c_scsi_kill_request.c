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
struct scsi_target {scalar_t__ can_queue; int /*<<< orphan*/  target_busy; } ;
struct scsi_device {int /*<<< orphan*/  device_busy; int /*<<< orphan*/  iorequest_cnt; struct Scsi_Host* host; } ;
struct scsi_cmnd {int result; struct scsi_device* device; } ;
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_busy; } ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_complete_request (struct request*) ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 int /*<<< orphan*/  scsi_init_cmd_errh (struct scsi_cmnd*) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 

__attribute__((used)) static void scsi_kill_request(struct request *req, struct request_queue *q)
{
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);
	struct scsi_device *sdev;
	struct scsi_target *starget;
	struct Scsi_Host *shost;

	blk_start_request(req);

	scmd_printk(KERN_INFO, cmd, "killing request\n");

	sdev = cmd->device;
	starget = scsi_target(sdev);
	shost = sdev->host;
	scsi_init_cmd_errh(cmd);
	cmd->result = DID_NO_CONNECT << 16;
	atomic_inc(&cmd->device->iorequest_cnt);

	/*
	 * SCSI request completion path will do scsi_device_unbusy(),
	 * bump busy counts.  To bump the counters, we need to dance
	 * with the locks as normal issue path does.
	 */
	atomic_inc(&sdev->device_busy);
	atomic_inc(&shost->host_busy);
	if (starget->can_queue > 0)
		atomic_inc(&starget->target_busy);

	blk_complete_request(req);
}