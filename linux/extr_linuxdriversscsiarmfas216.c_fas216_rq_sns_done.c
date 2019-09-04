#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ Status; int /*<<< orphan*/  Message; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  sense_buffer; TYPE_2__ SCp; TYPE_1__* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  ses; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ FAS216_Info ;

/* Variables and functions */
 unsigned int DID_OK ; 
 scalar_t__ GOOD ; 
 int /*<<< orphan*/  LOG_CONNECT ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  fas216_log_target (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_eh_restore_cmnd (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void fas216_rq_sns_done(FAS216_Info *info, struct scsi_cmnd *SCpnt,
			       unsigned int result)
{
	fas216_log_target(info, LOG_CONNECT, SCpnt->device->id,
		   "request sense complete, result=0x%04x%02x%02x",
		   result, SCpnt->SCp.Message, SCpnt->SCp.Status);

	if (result != DID_OK || SCpnt->SCp.Status != GOOD)
		/*
		 * Something went wrong.  Make sure that we don't
		 * have valid data in the sense buffer that could
		 * confuse the higher levels.
		 */
		memset(SCpnt->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
//printk("scsi%d.%c: sense buffer: ", info->host->host_no, '0' + SCpnt->device->id);
//{ int i; for (i = 0; i < 32; i++) printk("%02x ", SCpnt->sense_buffer[i]); printk("\n"); }
	/*
	 * Note that we don't set SCpnt->result, since that should
	 * reflect the status of the command that we were asked by
	 * the upper layers to process.  This would have been set
	 * correctly by fas216_std_done.
	 */
	scsi_eh_restore_cmnd(SCpnt, &info->ses);
	SCpnt->scsi_done(SCpnt);
}