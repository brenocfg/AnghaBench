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
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct TYPE_5__ {int /*<<< orphan*/  ProcessId; } ;
struct smb2_lock_req {int /*<<< orphan*/  VolatileFileId; int /*<<< orphan*/  PersistentFileId; int /*<<< orphan*/  LockCount; TYPE_1__ sync_hdr; } ;
struct smb2_lock_element {int dummy; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_locks; } ;
struct TYPE_7__ {TYPE_2__ cifs_stats; } ;
struct cifs_tcon {TYPE_4__* ses; int /*<<< orphan*/  tid; TYPE_3__ stats; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;
struct TYPE_8__ {int /*<<< orphan*/  Suid; } ;

/* Variables and functions */
 int CIFS_NO_RSP_BUF ; 
 int CIFS_TRANSFORM_REQ ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB2_LOCK ; 
 int /*<<< orphan*/  SMB2_LOCK_HE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int const) ; 
 int cifs_send_recv (unsigned int const,TYPE_4__*,struct smb_rqst*,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb2_lock_req*) ; 
 int /*<<< orphan*/  cifs_stats_fail_inc (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int const) ; 
 int /*<<< orphan*/  cpu_to_le32 (int const) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 
 scalar_t__ smb3_encryption_required (struct cifs_tcon*) ; 
 int /*<<< orphan*/  trace_smb3_lock_err (unsigned int const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
smb2_lockv(const unsigned int xid, struct cifs_tcon *tcon,
	   const __u64 persist_fid, const __u64 volatile_fid, const __u32 pid,
	   const __u32 num_lock, struct smb2_lock_element *buf)
{
	struct smb_rqst rqst;
	int rc = 0;
	struct smb2_lock_req *req = NULL;
	struct kvec iov[2];
	struct kvec rsp_iov;
	int resp_buf_type;
	unsigned int count;
	int flags = CIFS_NO_RSP_BUF;
	unsigned int total_len;

	cifs_dbg(FYI, "smb2_lockv num lock %d\n", num_lock);

	rc = smb2_plain_req_init(SMB2_LOCK, tcon, (void **) &req, &total_len);
	if (rc)
		return rc;

	if (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->sync_hdr.ProcessId = cpu_to_le32(pid);
	req->LockCount = cpu_to_le16(num_lock);

	req->PersistentFileId = persist_fid;
	req->VolatileFileId = volatile_fid;

	count = num_lock * sizeof(struct smb2_lock_element);

	iov[0].iov_base = (char *)req;
	iov[0].iov_len = total_len - sizeof(struct smb2_lock_element);
	iov[1].iov_base = (char *)buf;
	iov[1].iov_len = count;

	cifs_stats_inc(&tcon->stats.cifs_stats.num_locks);

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = 2;

	rc = cifs_send_recv(xid, tcon->ses, &rqst, &resp_buf_type, flags,
			    &rsp_iov);
	cifs_small_buf_release(req);
	if (rc) {
		cifs_dbg(FYI, "Send error in smb2_lockv = %d\n", rc);
		cifs_stats_fail_inc(tcon, SMB2_LOCK_HE);
		trace_smb3_lock_err(xid, persist_fid, tcon->tid,
				    tcon->ses->Suid, rc);
	}

	return rc;
}