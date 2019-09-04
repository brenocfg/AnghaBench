#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {TYPE_3__* device; } ;
struct TYPE_8__ {int aborts; } ;
struct TYPE_12__ {int /*<<< orphan*/  busyluns; TYPE_2__* host; TYPE_1__ stats; } ;
struct TYPE_11__ {scalar_t__ hostdata; } ;
struct TYPE_10__ {int id; int lun; TYPE_4__* host; } ;
struct TYPE_9__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_5__ AS_Host ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int acornscsi_do_abort (TYPE_5__*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  acornscsi_dumplog (TYPE_5__*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
#define  res_not_running 131 
#define  res_snooze 130 
#define  res_success 129 
#define  res_success_clear 128 

int acornscsi_abort(struct scsi_cmnd *SCpnt)
{
	AS_Host *host = (AS_Host *) SCpnt->device->host->hostdata;
	int result;

	host->stats.aborts += 1;

#if (DEBUG & DEBUG_ABORT)
	{
		int asr, ssr;
		asr = sbic_arm_read(host, SBIC_ASR);
		ssr = sbic_arm_read(host, SBIC_SSR);

		printk(KERN_WARNING "acornscsi_abort: ");
		print_sbic_status(asr, ssr, host->scsi.phase);
		acornscsi_dumplog(host, SCpnt->device->id);
	}
#endif

	printk("scsi%d: ", host->host->host_no);

	switch (acornscsi_do_abort(host, SCpnt)) {
	/*
	 * We managed to find the command and cleared it out.
	 * We do not expect the command to be executing on the
	 * target, but we have set the busylun bit.
	 */
	case res_success_clear:
//#if (DEBUG & DEBUG_ABORT)
		printk("clear ");
//#endif
		clear_bit(SCpnt->device->id * 8 +
			  (u8)(SCpnt->device->lun & 0x7), host->busyluns);

	/*
	 * We found the command, and cleared it out.  Either
	 * the command is still known to be executing on the
	 * target, or the busylun bit is not set.
	 */
	case res_success:
//#if (DEBUG & DEBUG_ABORT)
		printk("success\n");
//#endif
		result = SUCCESS;
		break;

	/*
	 * We did find the command, but unfortunately we couldn't
	 * unhook it from ourselves.  Wait some more, and if it
	 * still doesn't complete, reset the interface.
	 */
	case res_snooze:
//#if (DEBUG & DEBUG_ABORT)
		printk("snooze\n");
//#endif
		result = FAILED;
		break;

	/*
	 * The command could not be found (either because it completed,
	 * or it got dropped.
	 */
	default:
	case res_not_running:
		acornscsi_dumplog(host, SCpnt->device->id);
		result = FAILED;
//#if (DEBUG & DEBUG_ABORT)
		printk("not running\n");
//#endif
		break;
	}

	return result;
}