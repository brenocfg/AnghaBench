#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct smb2_tree_disconnect_req {int dummy; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct cifs_tcon {struct cifs_ses* ses; scalar_t__ need_reconnect; } ;
struct cifs_ses {scalar_t__ need_reconnect; int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int CIFS_NO_RSP_BUF ; 
 int CIFS_TRANSFORM_REQ ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB2_TREE_DISCONNECT ; 
 int /*<<< orphan*/  SMB2_TREE_DISCONNECT_HE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int cifs_send_recv (unsigned int const,struct cifs_ses*,struct smb_rqst*,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb2_tree_disconnect_req*) ; 
 int /*<<< orphan*/  cifs_stats_fail_inc (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 
 scalar_t__ smb3_encryption_required (struct cifs_tcon*) ; 

int
SMB2_tdis(const unsigned int xid, struct cifs_tcon *tcon)
{
	struct smb_rqst rqst;
	struct smb2_tree_disconnect_req *req; /* response is trivial */
	int rc = 0;
	struct cifs_ses *ses = tcon->ses;
	int flags = 0;
	unsigned int total_len;
	struct kvec iov[1];
	struct kvec rsp_iov;
	int resp_buf_type;

	cifs_dbg(FYI, "Tree Disconnect\n");

	if (!ses || !(ses->server))
		return -EIO;

	if ((tcon->need_reconnect) || (tcon->ses->need_reconnect))
		return 0;

	rc = smb2_plain_req_init(SMB2_TREE_DISCONNECT, tcon, (void **) &req,
			     &total_len);
	if (rc)
		return rc;

	if (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	flags |= CIFS_NO_RSP_BUF;

	iov[0].iov_base = (char *)req;
	iov[0].iov_len = total_len;

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cifs_send_recv(xid, ses, &rqst, &resp_buf_type, flags, &rsp_iov);
	cifs_small_buf_release(req);
	if (rc)
		cifs_stats_fail_inc(tcon, SMB2_TREE_DISCONNECT_HE);

	return rc;
}