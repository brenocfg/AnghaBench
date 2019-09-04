#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;scalar_t__ tag; int /*<<< orphan*/  result; void* host_scribble; TYPE_2__* device; } ;
struct TYPE_15__ {scalar_t__ phase; } ;
struct TYPE_14__ {int /*<<< orphan*/  issue; } ;
struct TYPE_13__ {int queues; } ;
struct TYPE_16__ {int /*<<< orphan*/  host_lock; TYPE_5__ scsi; TYPE_4__ queues; TYPE_3__ stats; } ;
struct TYPE_12__ {TYPE_1__* host; } ;
struct TYPE_11__ {scalar_t__ hostdata; } ;
typedef  TYPE_6__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_CONNECT ; 
 scalar_t__ PHASE_IDLE ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_6__*) ; 
 int /*<<< orphan*/  fas216_kick (TYPE_6__*) ; 
 int /*<<< orphan*/  fas216_log_command (TYPE_6__*,int /*<<< orphan*/ ,struct scsi_cmnd*,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  fas216_log_target (TYPE_6__*,int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ fas216_std_done ; 
 int /*<<< orphan*/  init_SCp (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  queue_add_cmd_ordered (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fas216_queue_command_lck(struct scsi_cmnd *SCpnt,
			 void (*done)(struct scsi_cmnd *))
{
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	int result;

	fas216_checkmagic(info);

	fas216_log_command(info, LOG_CONNECT, SCpnt,
			   "received command (%p)", SCpnt);

	SCpnt->scsi_done = done;
	SCpnt->host_scribble = (void *)fas216_std_done;
	SCpnt->result = 0;

	init_SCp(SCpnt);

	info->stats.queues += 1;
	SCpnt->tag = 0;

	spin_lock(&info->host_lock);

	/*
	 * Add command into execute queue and let it complete under
	 * whatever scheme we're using.
	 */
	result = !queue_add_cmd_ordered(&info->queues.issue, SCpnt);

	/*
	 * If we successfully added the command,
	 * kick the interface to get it moving.
	 */
	if (result == 0 && info->scsi.phase == PHASE_IDLE)
		fas216_kick(info);
	spin_unlock(&info->host_lock);

	fas216_log_target(info, LOG_CONNECT, -1, "queue %s",
		result ? "failure" : "success");

	return result;
}