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
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct TYPE_2__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  SessionId; } ;
struct smb2_logoff_req {TYPE_1__ sync_hdr; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct cifs_ses {int session_flags; int /*<<< orphan*/  Suid; scalar_t__ need_reconnect; struct TCP_Server_Info* server; } ;
struct TCP_Server_Info {scalar_t__ sign; } ;

/* Variables and functions */
 int CIFS_NO_RSP_BUF ; 
 int CIFS_TRANSFORM_REQ ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB2_FLAGS_SIGNED ; 
 int /*<<< orphan*/  SMB2_LOGOFF ; 
 int SMB2_SESSION_FLAG_ENCRYPT_DATA ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct cifs_ses*) ; 
 int cifs_send_recv (unsigned int const,struct cifs_ses*,struct smb_rqst*,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb2_logoff_req*) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,unsigned int*) ; 

int
SMB2_logoff(const unsigned int xid, struct cifs_ses *ses)
{
	struct smb_rqst rqst;
	struct smb2_logoff_req *req; /* response is also trivial struct */
	int rc = 0;
	struct TCP_Server_Info *server;
	int flags = 0;
	unsigned int total_len;
	struct kvec iov[1];
	struct kvec rsp_iov;
	int resp_buf_type;

	cifs_dbg(FYI, "disconnect session %p\n", ses);

	if (ses && (ses->server))
		server = ses->server;
	else
		return -EIO;

	/* no need to send SMB logoff if uid already closed due to reconnect */
	if (ses->need_reconnect)
		goto smb2_session_already_dead;

	rc = smb2_plain_req_init(SMB2_LOGOFF, NULL, (void **) &req, &total_len);
	if (rc)
		return rc;

	 /* since no tcon, smb2_init can not do this, so do here */
	req->sync_hdr.SessionId = ses->Suid;

	if (ses->session_flags & SMB2_SESSION_FLAG_ENCRYPT_DATA)
		flags |= CIFS_TRANSFORM_REQ;
	else if (server->sign)
		req->sync_hdr.Flags |= SMB2_FLAGS_SIGNED;

	flags |= CIFS_NO_RSP_BUF;

	iov[0].iov_base = (char *)req;
	iov[0].iov_len = total_len;

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cifs_send_recv(xid, ses, &rqst, &resp_buf_type, flags, &rsp_iov);
	cifs_small_buf_release(req);
	/*
	 * No tcon so can't do
	 * cifs_stats_inc(&tcon->stats.smb2_stats.smb2_com_fail[SMB2...]);
	 */

smb2_session_already_dead:
	return rc;
}