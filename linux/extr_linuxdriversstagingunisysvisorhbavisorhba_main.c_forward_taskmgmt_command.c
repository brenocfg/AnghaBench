#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct visorhba_devdata {int /*<<< orphan*/  idr; TYPE_4__* dev; int /*<<< orphan*/  privlock; scalar_t__ serverchangingstate; scalar_t__ serverdown; } ;
struct TYPE_6__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {int tasktype; int handle; TYPE_2__ vdest; } ;
struct uiscmdrsp {TYPE_3__ scsitaskmgmt; int /*<<< orphan*/  cmdtype; } ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; TYPE_1__* host; } ;
typedef  enum task_mgmt_types { ____Placeholder_task_mgmt_types } task_mgmt_types ;
struct TYPE_8__ {int /*<<< orphan*/  visorchannel; } ;
struct TYPE_5__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SCSITASKMGMT_TYPE ; 
 int FAILED ; 
 int /*<<< orphan*/  IOCHAN_TO_IOPART ; 
 int SUCCESS ; 
 int add_scsipending_entry (struct visorhba_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_scsitaskmgmt_handles (int /*<<< orphan*/ *,struct uiscmdrsp*) ; 
 int /*<<< orphan*/  del_scsipending_ent (struct visorhba_devdata*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct uiscmdrsp* get_scsipending_cmdrsp (struct visorhba_devdata*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  setup_scsitaskmgmt_handles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct uiscmdrsp*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ visorchannel_signalinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uiscmdrsp*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int forward_taskmgmt_command(enum task_mgmt_types tasktype,
				    struct scsi_device *scsidev)
{
	struct uiscmdrsp *cmdrsp;
	struct visorhba_devdata *devdata =
		(struct visorhba_devdata *)scsidev->host->hostdata;
	int notifyresult = 0xffff;
	wait_queue_head_t notifyevent;
	int scsicmd_id = 0;

	if (devdata->serverdown || devdata->serverchangingstate)
		return FAILED;

	scsicmd_id = add_scsipending_entry(devdata, CMD_SCSITASKMGMT_TYPE,
					   NULL);
	if (scsicmd_id < 0)
		return FAILED;

	cmdrsp = get_scsipending_cmdrsp(devdata, scsicmd_id);

	init_waitqueue_head(&notifyevent);

	/* issue TASK_MGMT_ABORT_TASK */
	cmdrsp->cmdtype = CMD_SCSITASKMGMT_TYPE;
	setup_scsitaskmgmt_handles(&devdata->idr, &devdata->privlock, cmdrsp,
				   &notifyevent, &notifyresult);

	/* save destination */
	cmdrsp->scsitaskmgmt.tasktype = tasktype;
	cmdrsp->scsitaskmgmt.vdest.channel = scsidev->channel;
	cmdrsp->scsitaskmgmt.vdest.id = scsidev->id;
	cmdrsp->scsitaskmgmt.vdest.lun = scsidev->lun;
	cmdrsp->scsitaskmgmt.handle = scsicmd_id;

	dev_dbg(&scsidev->sdev_gendev,
		"visorhba: initiating type=%d taskmgmt command\n", tasktype);
	if (visorchannel_signalinsert(devdata->dev->visorchannel,
				      IOCHAN_TO_IOPART,
				      cmdrsp))
		goto err_del_scsipending_ent;

	/* It can take the Service Partition up to 35 seconds to complete
	 * an IO in some cases, so wait 45 seconds and error out
	 */
	if (!wait_event_timeout(notifyevent, notifyresult != 0xffff,
				msecs_to_jiffies(45000)))
		goto err_del_scsipending_ent;

	dev_dbg(&scsidev->sdev_gendev,
		"visorhba: taskmgmt type=%d success; result=0x%x\n",
		 tasktype, notifyresult);
	cleanup_scsitaskmgmt_handles(&devdata->idr, cmdrsp);
	return SUCCESS;

err_del_scsipending_ent:
	dev_dbg(&scsidev->sdev_gendev,
		"visorhba: taskmgmt type=%d not executed\n", tasktype);
	del_scsipending_ent(devdata, scsicmd_id);
	cleanup_scsitaskmgmt_handles(&devdata->idr, cmdrsp);
	return FAILED;
}