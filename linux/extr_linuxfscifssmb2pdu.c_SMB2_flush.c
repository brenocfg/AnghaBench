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
typedef  void* u64 ;
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct smb2_flush_req {void* VolatileFileId; void* PersistentFileId; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct cifs_tcon {int /*<<< orphan*/  tid; struct cifs_ses* ses; } ;
struct cifs_ses {int /*<<< orphan*/  Suid; int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int CIFS_TRANSFORM_REQ ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB2_FLUSH ; 
 int /*<<< orphan*/  SMB2_FLUSH_HE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int cifs_send_recv (unsigned int const,struct cifs_ses*,struct smb_rqst*,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb2_flush_req*) ; 
 int /*<<< orphan*/  cifs_stats_fail_inc (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rsp_buf (int,char*) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 
 scalar_t__ smb3_encryption_required (struct cifs_tcon*) ; 
 int /*<<< orphan*/  trace_smb3_flush_err (unsigned int const,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
SMB2_flush(const unsigned int xid, struct cifs_tcon *tcon, u64 persistent_fid,
	   u64 volatile_fid)
{
	struct smb_rqst rqst;
	struct smb2_flush_req *req;
	struct cifs_ses *ses = tcon->ses;
	struct kvec iov[1];
	struct kvec rsp_iov;
	int resp_buftype;
	int rc = 0;
	int flags = 0;
	unsigned int total_len;

	cifs_dbg(FYI, "Flush\n");

	if (!ses || !(ses->server))
		return -EIO;

	rc = smb2_plain_req_init(SMB2_FLUSH, tcon, (void **) &req, &total_len);
	if (rc)
		return rc;

	if (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = volatile_fid;

	iov[0].iov_base = (char *)req;
	iov[0].iov_len = total_len;

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 1;

	rc = cifs_send_recv(xid, ses, &rqst, &resp_buftype, flags, &rsp_iov);
	cifs_small_buf_release(req);

	if (rc != 0) {
		cifs_stats_fail_inc(tcon, SMB2_FLUSH_HE);
		trace_smb3_flush_err(xid, persistent_fid, tcon->tid, ses->Suid,
				     rc);
	}

	free_rsp_buf(resp_buftype, rsp_iov.iov_base);
	return rc;
}