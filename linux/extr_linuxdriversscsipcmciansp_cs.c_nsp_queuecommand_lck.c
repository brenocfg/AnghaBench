#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ buffers_residual; TYPE_5__* buffer; scalar_t__ this_residual; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  phase; scalar_t__ sent_command; int /*<<< orphan*/  have_data_in; scalar_t__ Message; int /*<<< orphan*/  Status; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;int result; TYPE_3__ SCp; TYPE_2__* device; } ;
struct TYPE_9__ {struct scsi_cmnd* CurrentSC; } ;
typedef  TYPE_4__ nsp_hw_data ;
struct TYPE_10__ {scalar_t__ length; } ;
struct TYPE_7__ {int /*<<< orphan*/  lun; TYPE_1__* host; } ;
struct TYPE_6__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BUFFER_ADDR ; 
 int /*<<< orphan*/  CHECK_CONDITION ; 
 int DID_BAD_TARGET ; 
 int DID_BUS_BUSY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IO_UNKNOWN ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  NSP_DEBUG_QUEUECOMMAND ; 
 int /*<<< orphan*/  PH_UNDETERMINED ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nsp_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp_scsi_done (struct scsi_cmnd*) ; 
 scalar_t__ nsphw_start_selection (struct scsi_cmnd*) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 TYPE_5__* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  show_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  target ; 

__attribute__((used)) static int nsp_queuecommand_lck(struct scsi_cmnd *SCpnt,
			    void (*done)(struct scsi_cmnd *))
{
#ifdef NSP_DEBUG
	/*unsigned int host_id = SCpnt->device->host->this_id;*/
	/*unsigned int base    = SCpnt->device->host->io_port;*/
	unsigned char target = scmd_id(SCpnt);
#endif
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_QUEUECOMMAND,
		"SCpnt=0x%p target=%d lun=%llu sglist=0x%p bufflen=%d sg_count=%d",
		SCpnt, target, SCpnt->device->lun, scsi_sglist(SCpnt),
		scsi_bufflen(SCpnt), scsi_sg_count(SCpnt));
	//nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "before CurrentSC=0x%p", data->CurrentSC);

	SCpnt->scsi_done	= done;

	if (data->CurrentSC != NULL) {
		nsp_msg(KERN_DEBUG, "CurrentSC!=NULL this can't be happen");
		SCpnt->result   = DID_BAD_TARGET << 16;
		nsp_scsi_done(SCpnt);
		return 0;
	}

#if 0
	/* XXX: pcmcia-cs generates SCSI command with "scsi_info" utility.
	        This makes kernel crash when suspending... */
	if (data->ScsiInfo->stop != 0) {
		nsp_msg(KERN_INFO, "suspending device. reject command.");
		SCpnt->result  = DID_BAD_TARGET << 16;
		nsp_scsi_done(SCpnt);
		return SCSI_MLQUEUE_HOST_BUSY;
	}
#endif

	show_command(SCpnt);

	data->CurrentSC		= SCpnt;

	SCpnt->SCp.Status	= CHECK_CONDITION;
	SCpnt->SCp.Message	= 0;
	SCpnt->SCp.have_data_in = IO_UNKNOWN;
	SCpnt->SCp.sent_command = 0;
	SCpnt->SCp.phase	= PH_UNDETERMINED;
	scsi_set_resid(SCpnt, scsi_bufflen(SCpnt));

	/* setup scratch area
	   SCp.ptr		: buffer pointer
	   SCp.this_residual	: buffer length
	   SCp.buffer		: next buffer
	   SCp.buffers_residual : left buffers in list
	   SCp.phase		: current state of the command */
	if (scsi_bufflen(SCpnt)) {
		SCpnt->SCp.buffer	    = scsi_sglist(SCpnt);
		SCpnt->SCp.ptr		    = BUFFER_ADDR;
		SCpnt->SCp.this_residual    = SCpnt->SCp.buffer->length;
		SCpnt->SCp.buffers_residual = scsi_sg_count(SCpnt) - 1;
	} else {
		SCpnt->SCp.ptr		    = NULL;
		SCpnt->SCp.this_residual    = 0;
		SCpnt->SCp.buffer	    = NULL;
		SCpnt->SCp.buffers_residual = 0;
	}

	if (nsphw_start_selection(SCpnt) == FALSE) {
		nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "selection fail");
		SCpnt->result   = DID_BUS_BUSY << 16;
		nsp_scsi_done(SCpnt);
		return 0;
	}


	//nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "out");
#ifdef NSP_DEBUG
	data->CmdId++;
#endif
	return 0;
}