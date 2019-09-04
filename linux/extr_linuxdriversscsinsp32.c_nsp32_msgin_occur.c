#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  nsp32_sgtable ;
struct TYPE_13__ {unsigned char* msginbuf; int msgin_len; scalar_t__ msgout_len; TYPE_3__* cur_lunt; TYPE_7__* cur_target; } ;
typedef  TYPE_4__ nsp32_hw_data ;
struct TYPE_14__ {int sync_flag; } ;
struct TYPE_12__ {int msgin03; int cur_entry; int /*<<< orphan*/  sglun_paddr; } ;
struct TYPE_11__ {TYPE_1__* host; } ;
struct TYPE_10__ {unsigned int io_port; scalar_t__ hostdata; } ;

/* Variables and functions */
 unsigned short AUTO_ATN ; 
 unsigned short AUTO_MSGIN_00_OR_04 ; 
 unsigned short AUTO_MSGIN_02 ; 
 unsigned short AUTO_MSGIN_03 ; 
 long CLRCOUNTER_ALLMASK ; 
 int /*<<< orphan*/  CLR_COUNTER ; 
#define  COMMAND_COMPLETE 141 
 unsigned short DATA_IN_PHASE ; 
 unsigned short DATA_OUT_PHASE ; 
#define  DISCONNECT 140 
#define  EXTENDED_EXTENDED_IDENTIFY 139 
#define  EXTENDED_MESSAGE 138 
#define  EXTENDED_MODIFY_DATA_POINTER 137 
#define  EXTENDED_SDTR 136 
 int /*<<< orphan*/  EXTENDED_SDTR_LEN ; 
#define  EXTENDED_WDTR 135 
 void* FALSE ; 
#define  INITIATE_RECOVERY 134 
 unsigned long IRQSTATUS_RESELECT_OCCUER ; 
 int /*<<< orphan*/  KERN_WARNING ; 
#define  LINKED_CMD_COMPLETE 133 
#define  LINKED_FLG_CMD_COMPLETE 132 
#define  MESSAGE_REJECT 131 
 unsigned short MSGIN_02_VALID ; 
 int /*<<< orphan*/  NEGATE ; 
 int /*<<< orphan*/  NSP32_DEBUG_MSGINOCCUR ; 
#define  RESTORE_POINTERS 130 
 int /*<<< orphan*/  SAVED_SACK_CNT ; 
#define  SAVE_POINTERS 129 
 int /*<<< orphan*/  SCSI_DATA_IN ; 
 int /*<<< orphan*/  SCSI_MSG_OUT ; 
 int SDTR_DONE ; 
 int SDTR_INITIATOR ; 
 int SDTR_TARGET ; 
 int /*<<< orphan*/  SGT_ADR ; 
#define  SIMPLE_QUEUE_TAG 128 
 int TRUE ; 
 int /*<<< orphan*/  nsp32_adjust_busfree (struct scsi_cmnd*,unsigned int) ; 
 int /*<<< orphan*/  nsp32_analyze_sdtr (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_build_reject (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*,...) ; 
 unsigned char nsp32_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int nsp32_read4 (unsigned int,int /*<<< orphan*/ ) ; 
 int nsp32_reselection (struct scsi_cmnd*,unsigned char) ; 
 int /*<<< orphan*/  nsp32_restart_autoscsi (struct scsi_cmnd*,unsigned short) ; 
 int /*<<< orphan*/  nsp32_sack_assert (TYPE_4__*) ; 
 int /*<<< orphan*/  nsp32_sack_negate (TYPE_4__*) ; 
 int /*<<< orphan*/  nsp32_set_async (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  nsp32_wait_req (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write4 (unsigned int,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void nsp32_msgin_occur(struct scsi_cmnd     *SCpnt,
			      unsigned long  irq_status,
			      unsigned short execph)
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	unsigned int   base = SCpnt->device->host->io_port;
	unsigned char  msg;
	unsigned char  msgtype;
	unsigned char  newlun;
	unsigned short command  = 0;
	int            msgclear = TRUE;
	long           new_sgtp;
	int            ret;

	/*
	 * read first message
	 *    Use SCSIDATA_W_ACK instead of SCSIDATAIN, because the procedure
	 *    of Message-In have to be processed before sending back SCSI ACK.
	 */
	msg = nsp32_read1(base, SCSI_DATA_IN);
	data->msginbuf[(unsigned char)data->msgin_len] = msg;
	msgtype = data->msginbuf[0];
	nsp32_dbg(NSP32_DEBUG_MSGINOCCUR,
		  "enter: msglen: 0x%x msgin: 0x%x msgtype: 0x%x",
		  data->msgin_len, msg, msgtype);

	/*
	 * TODO: We need checking whether bus phase is message in?
	 */

	/*
	 * assert SCSI ACK
	 */
	nsp32_sack_assert(data);

	/*
	 * processing IDENTIFY
	 */
	if (msgtype & 0x80) {
		if (!(irq_status & IRQSTATUS_RESELECT_OCCUER)) {
			/* Invalid (non reselect) phase */
			goto reject;
		}

		newlun = msgtype & 0x1f; /* TODO: SPI-3 compliant? */
		ret = nsp32_reselection(SCpnt, newlun);
		if (ret == TRUE) {
			goto restart;
		} else {
			goto reject;
		}
	}
	
	/*
	 * processing messages except for IDENTIFY
	 *
	 * TODO: Messages are all SCSI-2 terminology. SCSI-3 compliance is TODO.
	 */
	switch (msgtype) {
	/*
	 * 1-byte message
	 */
	case COMMAND_COMPLETE:
	case DISCONNECT:
		/*
		 * These messages should not be occurred.
		 * They should be processed on AutoSCSI sequencer.
		 */
		nsp32_msg(KERN_WARNING, 
			   "unexpected message of AutoSCSI MsgIn: 0x%x", msg);
		break;
		
	case RESTORE_POINTERS:
		/*
		 * AutoMsgIn03 is disabled, and HBA gets this message.
		 */

		if ((execph & DATA_IN_PHASE) || (execph & DATA_OUT_PHASE)) {
			unsigned int s_sacklen;

			s_sacklen = nsp32_read4(base, SAVED_SACK_CNT);
			if ((execph & MSGIN_02_VALID) && (s_sacklen > 0)) {
				nsp32_adjust_busfree(SCpnt, s_sacklen);
			} else {
				/* No need to rewrite SGT */
			}
		}
		data->cur_lunt->msgin03 = FALSE;

		/* Update with the new value */

		/* reset SACK/SavedACK counter (or ALL clear?) */
		nsp32_write4(base, CLR_COUNTER, CLRCOUNTER_ALLMASK);

		/*
		 * set new sg pointer
		 */
		new_sgtp = data->cur_lunt->sglun_paddr + 
			(data->cur_lunt->cur_entry * sizeof(nsp32_sgtable));
		nsp32_write4(base, SGT_ADR, new_sgtp);

		break;

	case SAVE_POINTERS:
		/*
		 * These messages should not be occurred.
		 * They should be processed on AutoSCSI sequencer.
		 */
		nsp32_msg (KERN_WARNING, 
			   "unexpected message of AutoSCSI MsgIn: SAVE_POINTERS");
		
		break;
		
	case MESSAGE_REJECT:
		/* If previous message_out is sending SDTR, and get 
		   message_reject from target, SDTR negotiation is failed */
		if (data->cur_target->sync_flag &
				(SDTR_INITIATOR | SDTR_TARGET)) {
			/*
			 * Current target is negotiating SDTR, but it's
			 * failed.  Fall back to async transfer mode, and set
			 * SDTR_DONE.
			 */
			nsp32_set_async(data, data->cur_target);
			data->cur_target->sync_flag &= ~SDTR_INITIATOR;
			data->cur_target->sync_flag |= SDTR_DONE;

		}
		break;

	case LINKED_CMD_COMPLETE:
	case LINKED_FLG_CMD_COMPLETE:
		/* queue tag is not supported currently */
		nsp32_msg (KERN_WARNING, 
			   "unsupported message: 0x%x", msgtype);
		break;

	case INITIATE_RECOVERY:
		/* staring ECA (Extended Contingent Allegiance) state. */
		/* This message is declined in SPI2 or later. */

		goto reject;

	/*
	 * 2-byte message
	 */
	case SIMPLE_QUEUE_TAG:
	case 0x23:
		/*
		 * 0x23: Ignore_Wide_Residue is not declared in scsi.h.
		 * No support is needed.
		 */
		if (data->msgin_len >= 1) {
			goto reject;
		}

		/* current position is 1-byte of 2 byte */
		msgclear = FALSE;

		break;

	/*
	 * extended message
	 */
	case EXTENDED_MESSAGE:
		if (data->msgin_len < 1) {
			/*
			 * Current position does not reach 2-byte
			 * (2-byte is extended message length).
			 */
			msgclear = FALSE;
			break;
		}

		if ((data->msginbuf[1] + 1) > data->msgin_len) {
			/*
			 * Current extended message has msginbuf[1] + 2
			 * (msgin_len starts counting from 0, so buf[1] + 1).
			 * If current message position is not finished,
			 * continue receiving message.
			 */
			msgclear = FALSE;
			break;
		}

		/*
		 * Reach here means regular length of each type of 
		 * extended messages.
		 */
		switch (data->msginbuf[2]) {
		case EXTENDED_MODIFY_DATA_POINTER:
			/* TODO */
			goto reject; /* not implemented yet */
			break;

		case EXTENDED_SDTR:
			/*
			 * Exchange this message between initiator and target.
			 */
			if (data->msgin_len != EXTENDED_SDTR_LEN + 1) {
				/*
				 * received inappropriate message.
				 */
				goto reject;
				break;
			}

			nsp32_analyze_sdtr(SCpnt);

			break;

		case EXTENDED_EXTENDED_IDENTIFY:
			/* SCSI-I only, not supported. */
			goto reject; /* not implemented yet */

			break;

		case EXTENDED_WDTR:
			goto reject; /* not implemented yet */

			break;
			
		default:
			goto reject;
		}
		break;
		
	default:
		goto reject;
	}

 restart:
	if (msgclear == TRUE) {
		data->msgin_len = 0;

		/*
		 * If restarting AutoSCSI, but there are some message to out
		 * (msgout_len > 0), set AutoATN, and set SCSIMSGOUT as 0
		 * (MV_VALID = 0). When commandcontrol is written with
		 * AutoSCSI restart, at the same time MsgOutOccur should be
		 * happened (however, such situation is really possible...?).
		 */
		if (data->msgout_len > 0) {	
			nsp32_write4(base, SCSI_MSG_OUT, 0);
			command |= AUTO_ATN;
		}

		/*
		 * restart AutoSCSI
		 * If it's failed, COMMANDCONTROL_AUTO_COMMAND_PHASE is needed.
		 */
		command |= (AUTO_MSGIN_00_OR_04 | AUTO_MSGIN_02);

		/*
		 * If current msgin03 is TRUE, then flag on.
		 */
		if (data->cur_lunt->msgin03 == TRUE) {
			command |= AUTO_MSGIN_03;
		}
		data->cur_lunt->msgin03 = FALSE;
	} else {
		data->msgin_len++;
	}

	/*
	 * restart AutoSCSI
	 */
	nsp32_restart_autoscsi(SCpnt, command);

	/*
	 * wait SCSI REQ negate for REQ-ACK handshake
	 */
	nsp32_wait_req(data, NEGATE);

	/*
	 * negate SCSI ACK
	 */
	nsp32_sack_negate(data);

	nsp32_dbg(NSP32_DEBUG_MSGINOCCUR, "exit");

	return;

 reject:
	nsp32_msg(KERN_WARNING, 
		  "invalid or unsupported MessageIn, rejected. "
		  "current msg: 0x%x (len: 0x%x), processing msg: 0x%x",
		  msg, data->msgin_len, msgtype);
	nsp32_build_reject(SCpnt);
	data->msgin_len = 0;

	goto restart;
}