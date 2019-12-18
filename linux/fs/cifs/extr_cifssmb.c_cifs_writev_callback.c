#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mid_q_entry {int mid_state; scalar_t__ resp_buf; struct cifs_writedata* callback_data; } ;
struct cifs_writedata {unsigned int bytes; int /*<<< orphan*/  work; int /*<<< orphan*/  result; TYPE_1__* cfile; } ;
struct cifs_tcon {TYPE_2__* ses; } ;
struct cifs_credits {int value; int /*<<< orphan*/  instance; } ;
struct TYPE_6__ {int /*<<< orphan*/  Count; int /*<<< orphan*/  CountHigh; } ;
typedef  TYPE_3__ WRITE_RSP ;
struct TYPE_5__ {int /*<<< orphan*/  server; } ;
struct TYPE_4__ {int /*<<< orphan*/  tlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteMidQEntry (struct mid_q_entry*) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSPC ; 
#define  MID_REQUEST_SUBMITTED 130 
#define  MID_RESPONSE_RECEIVED 129 
#define  MID_RETRY_NEEDED 128 
 int /*<<< orphan*/  add_credits (int /*<<< orphan*/ ,struct cifs_credits*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_check_receive (struct mid_q_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifsiod_wq ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_writev_callback(struct mid_q_entry *mid)
{
	struct cifs_writedata *wdata = mid->callback_data;
	struct cifs_tcon *tcon = tlink_tcon(wdata->cfile->tlink);
	unsigned int written;
	WRITE_RSP *smb = (WRITE_RSP *)mid->resp_buf;
	struct cifs_credits credits = { .value = 1, .instance = 0 };

	switch (mid->mid_state) {
	case MID_RESPONSE_RECEIVED:
		wdata->result = cifs_check_receive(mid, tcon->ses->server, 0);
		if (wdata->result != 0)
			break;

		written = le16_to_cpu(smb->CountHigh);
		written <<= 16;
		written += le16_to_cpu(smb->Count);
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
	default:
		wdata->result = -EIO;
		break;
	}

	queue_work(cifsiod_wq, &wdata->work);
	DeleteMidQEntry(mid);
	add_credits(tcon->ses->server, &credits, 0);
}