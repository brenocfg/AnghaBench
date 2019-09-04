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
struct smb_rqst {TYPE_1__* rq_iov; } ;
struct smb_hdr {int /*<<< orphan*/  smb_buf_length; scalar_t__ WordCount; int /*<<< orphan*/  Command; } ;
struct mid_q_entry {int /*<<< orphan*/  sequence_number; } ;
struct TCP_Server_Info {int /*<<< orphan*/  srv_mutex; int /*<<< orphan*/  sequence_number; } ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB_COM_NT_CANCEL ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int cifs_sign_smb (struct smb_hdr*,struct TCP_Server_Info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  get_mid (struct smb_hdr*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bcc (int /*<<< orphan*/ ,struct smb_hdr*) ; 
 int smb_send (struct TCP_Server_Info*,struct smb_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_nt_cancel(struct TCP_Server_Info *server, struct smb_rqst *rqst,
	       struct mid_q_entry *mid)
{
	int rc = 0;
	struct smb_hdr *in_buf = (struct smb_hdr *)rqst->rq_iov[0].iov_base;

	/* -4 for RFC1001 length and +2 for BCC field */
	in_buf->smb_buf_length = cpu_to_be32(sizeof(struct smb_hdr) - 4  + 2);
	in_buf->Command = SMB_COM_NT_CANCEL;
	in_buf->WordCount = 0;
	put_bcc(0, in_buf);

	mutex_lock(&server->srv_mutex);
	rc = cifs_sign_smb(in_buf, server, &mid->sequence_number);
	if (rc) {
		mutex_unlock(&server->srv_mutex);
		return rc;
	}

	/*
	 * The response to this call was already factored into the sequence
	 * number when the call went out, so we must adjust it back downward
	 * after signing here.
	 */
	--server->sequence_number;
	rc = smb_send(server, in_buf, be32_to_cpu(in_buf->smb_buf_length));
	if (rc < 0)
		server->sequence_number--;

	mutex_unlock(&server->srv_mutex);

	cifs_dbg(FYI, "issued NT_CANCEL for mid %u, rc = %d\n",
		 get_mid(in_buf), rc);

	return rc;
}