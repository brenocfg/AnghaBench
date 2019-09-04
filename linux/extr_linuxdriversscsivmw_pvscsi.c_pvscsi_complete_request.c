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
typedef  int u32 ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/ * cmnd; TYPE_1__* device; scalar_t__ sense_buffer; } ;
struct pvscsi_ctx {struct completion* abort_cmp; struct scsi_cmnd* cmd; } ;
struct pvscsi_adapter {int dummy; } ;
struct completion {int dummy; } ;
struct PVSCSIRingCmpDesc {int hostStatus; int scsiStatus; scalar_t__ dataLen; int /*<<< orphan*/  context; } ;
struct TYPE_2__ {int /*<<< orphan*/  sdev_gendev; } ;

/* Variables and functions */
#define  BTSTAT_ABORTQUEUE 149 
#define  BTSTAT_BADMSG 148 
#define  BTSTAT_BUSFREE 147 
#define  BTSTAT_BUSRESET 146 
#define  BTSTAT_DATARUN 145 
#define  BTSTAT_DATA_UNDERRUN 144 
#define  BTSTAT_DISCONNECT 143 
#define  BTSTAT_HAHARDWARE 142 
#define  BTSTAT_HASOFTWARE 141 
#define  BTSTAT_HATIMEOUT 140 
#define  BTSTAT_INVPHASE 139 
#define  BTSTAT_LINKED_COMMAND_COMPLETED 138 
#define  BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG 137 
#define  BTSTAT_LUNMISMATCH 136 
#define  BTSTAT_NORESPONSE 135 
#define  BTSTAT_RECVRST 134 
#define  BTSTAT_SCSIPARITY 133 
#define  BTSTAT_SELTIMEO 132 
#define  BTSTAT_SENSFAILED 131 
#define  BTSTAT_SENTRST 130 
#define  BTSTAT_SUCCESS 129 
#define  BTSTAT_TAGREJECT 128 
 int DID_BAD_TARGET ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_OK ; 
 int DID_PARITY ; 
 int DID_RESET ; 
 int DRIVER_INVALID ; 
 int DRIVER_SENSE ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int SAM_STAT_COMMAND_TERMINATED ; 
 int SAM_STAT_GOOD ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct scsi_cmnd*,int /*<<< orphan*/ ,struct pvscsi_ctx*,int,int,int) ; 
 struct pvscsi_ctx* pvscsi_get_context (struct pvscsi_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_release_context (struct pvscsi_adapter*,struct pvscsi_ctx*) ; 
 int /*<<< orphan*/  pvscsi_unmap_buffers (struct pvscsi_adapter*,struct pvscsi_ctx*) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void pvscsi_complete_request(struct pvscsi_adapter *adapter,
				    const struct PVSCSIRingCmpDesc *e)
{
	struct pvscsi_ctx *ctx;
	struct scsi_cmnd *cmd;
	struct completion *abort_cmp;
	u32 btstat = e->hostStatus;
	u32 sdstat = e->scsiStatus;

	ctx = pvscsi_get_context(adapter, e->context);
	cmd = ctx->cmd;
	abort_cmp = ctx->abort_cmp;
	pvscsi_unmap_buffers(adapter, ctx);
	pvscsi_release_context(adapter, ctx);
	if (abort_cmp) {
		/*
		 * The command was requested to be aborted. Just signal that
		 * the request completed and swallow the actual cmd completion
		 * here. The abort handler will post a completion for this
		 * command indicating that it got successfully aborted.
		 */
		complete(abort_cmp);
		return;
	}

	cmd->result = 0;
	if (sdstat != SAM_STAT_GOOD &&
	    (btstat == BTSTAT_SUCCESS ||
	     btstat == BTSTAT_LINKED_COMMAND_COMPLETED ||
	     btstat == BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG)) {
		if (sdstat == SAM_STAT_COMMAND_TERMINATED) {
			cmd->result = (DID_RESET << 16);
		} else {
			cmd->result = (DID_OK << 16) | sdstat;
			if (sdstat == SAM_STAT_CHECK_CONDITION &&
			    cmd->sense_buffer)
				cmd->result |= (DRIVER_SENSE << 24);
		}
	} else
		switch (btstat) {
		case BTSTAT_SUCCESS:
		case BTSTAT_LINKED_COMMAND_COMPLETED:
		case BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG:
			/* If everything went fine, let's move on..  */
			cmd->result = (DID_OK << 16);
			break;

		case BTSTAT_DATARUN:
		case BTSTAT_DATA_UNDERRUN:
			/* Report residual data in underruns */
			scsi_set_resid(cmd, scsi_bufflen(cmd) - e->dataLen);
			cmd->result = (DID_ERROR << 16);
			break;

		case BTSTAT_SELTIMEO:
			/* Our emulation returns this for non-connected devs */
			cmd->result = (DID_BAD_TARGET << 16);
			break;

		case BTSTAT_LUNMISMATCH:
		case BTSTAT_TAGREJECT:
		case BTSTAT_BADMSG:
			cmd->result = (DRIVER_INVALID << 24);
			/* fall through */

		case BTSTAT_HAHARDWARE:
		case BTSTAT_INVPHASE:
		case BTSTAT_HATIMEOUT:
		case BTSTAT_NORESPONSE:
		case BTSTAT_DISCONNECT:
		case BTSTAT_HASOFTWARE:
		case BTSTAT_BUSFREE:
		case BTSTAT_SENSFAILED:
			cmd->result |= (DID_ERROR << 16);
			break;

		case BTSTAT_SENTRST:
		case BTSTAT_RECVRST:
		case BTSTAT_BUSRESET:
			cmd->result = (DID_RESET << 16);
			break;

		case BTSTAT_ABORTQUEUE:
			cmd->result = (DID_BUS_BUSY << 16);
			break;

		case BTSTAT_SCSIPARITY:
			cmd->result = (DID_PARITY << 16);
			break;

		default:
			cmd->result = (DID_ERROR << 16);
			scmd_printk(KERN_DEBUG, cmd,
				    "Unknown completion status: 0x%x\n",
				    btstat);
	}

	dev_dbg(&cmd->device->sdev_gendev,
		"cmd=%p %x ctx=%p result=0x%x status=0x%x,%x\n",
		cmd, cmd->cmnd[0], ctx, cmd->result, btstat, sdstat);

	cmd->scsi_done(cmd);
}