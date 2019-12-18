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
struct TYPE_5__ {int /*<<< orphan*/  CreditRequest; } ;
struct smb2_write_rsp {TYPE_1__ sync_hdr; int /*<<< orphan*/  DataLength; } ;
struct mid_q_entry {int mid_state; scalar_t__ resp_buf; struct cifs_writedata* callback_data; } ;
struct cifs_writedata {scalar_t__ result; unsigned int bytes; int /*<<< orphan*/  work; int /*<<< orphan*/  offset; TYPE_3__* cfile; int /*<<< orphan*/ * mr; } ;
struct cifs_tcon {TYPE_4__* ses; int /*<<< orphan*/  tid; } ;
struct cifs_credits {int /*<<< orphan*/  instance; void* value; } ;
struct TCP_Server_Info {int /*<<< orphan*/  reconnect_instance; } ;
struct TYPE_8__ {int /*<<< orphan*/  Suid; struct TCP_Server_Info* server; } ;
struct TYPE_6__ {int /*<<< orphan*/  persistent_fid; } ;
struct TYPE_7__ {TYPE_2__ fid; int /*<<< orphan*/  tlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteMidQEntry (struct mid_q_entry*) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EIO ; 
 scalar_t__ ENOSPC ; 
#define  MID_REQUEST_SUBMITTED 131 
#define  MID_RESPONSE_MALFORMED 130 
#define  MID_RESPONSE_RECEIVED 129 
#define  MID_RETRY_NEEDED 128 
 int /*<<< orphan*/  SMB2_WRITE_HE ; 
 int /*<<< orphan*/  add_credits (struct TCP_Server_Info*,struct cifs_credits*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_stats_fail_inc (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifsiod_wq ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ smb2_check_receive (struct mid_q_entry*,struct TCP_Server_Info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbd_deregister_mr (int /*<<< orphan*/ *) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_smb3_write_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_smb3_write_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 

__attribute__((used)) static void
smb2_writev_callback(struct mid_q_entry *mid)
{
	struct cifs_writedata *wdata = mid->callback_data;
	struct cifs_tcon *tcon = tlink_tcon(wdata->cfile->tlink);
	struct TCP_Server_Info *server = tcon->ses->server;
	unsigned int written;
	struct smb2_write_rsp *rsp = (struct smb2_write_rsp *)mid->resp_buf;
	struct cifs_credits credits = { .value = 0, .instance = 0 };

	switch (mid->mid_state) {
	case MID_RESPONSE_RECEIVED:
		credits.value = le16_to_cpu(rsp->sync_hdr.CreditRequest);
		credits.instance = server->reconnect_instance;
		wdata->result = smb2_check_receive(mid, server, 0);
		if (wdata->result != 0)
			break;

		written = le32_to_cpu(rsp->DataLength);
		/*
		 * Mask off high 16 bits when bytes written as returned
		 * by the server is greater than bytes requested by the
		 * client. OS/2 servers are known to set incorrect
		 * CountHigh values.
		 */
		if (written > wdata->bytes)
			written &= 0xFFFF;

		if (written < wdata->bytes)
			wdata->result = -ENOSPC;
		else
			wdata->bytes = written;
		break;
	case MID_REQUEST_SUBMITTED:
	case MID_RETRY_NEEDED:
		wdata->result = -EAGAIN;
		break;
	case MID_RESPONSE_MALFORMED:
		credits.value = le16_to_cpu(rsp->sync_hdr.CreditRequest);
		credits.instance = server->reconnect_instance;
		/* fall through */
	default:
		wdata->result = -EIO;
		break;
	}
#ifdef CONFIG_CIFS_SMB_DIRECT
	/*
	 * If this wdata has a memory registered, the MR can be freed
	 * The number of MRs available is limited, it's important to recover
	 * used MR as soon as I/O is finished. Hold MR longer in the later
	 * I/O process can possibly result in I/O deadlock due to lack of MR
	 * to send request on I/O retry
	 */
	if (wdata->mr) {
		smbd_deregister_mr(wdata->mr);
		wdata->mr = NULL;
	}
#endif
	if (wdata->result) {
		cifs_stats_fail_inc(tcon, SMB2_WRITE_HE);
		trace_smb3_write_err(0 /* no xid */,
				     wdata->cfile->fid.persistent_fid,
				     tcon->tid, tcon->ses->Suid, wdata->offset,
				     wdata->bytes, wdata->result);
	} else
		trace_smb3_write_done(0 /* no xid */,
				      wdata->cfile->fid.persistent_fid,
				      tcon->tid, tcon->ses->Suid,
				      wdata->offset, wdata->bytes);

	queue_work(cifsiod_wq, &wdata->work);
	DeleteMidQEntry(mid);
	add_credits(server, &credits, 0);
}