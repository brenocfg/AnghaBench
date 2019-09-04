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
typedef  void* u8 ;
typedef  void* u64 ;
typedef  unsigned int u32 ;
struct smb_rqst {unsigned int rq_nvec; struct kvec* rq_iov; } ;
struct smb2_set_info_rsp {int dummy; } ;
struct TYPE_2__ {void* ProcessId; } ;
struct smb2_set_info_req {void* BufferLength; int /*<<< orphan*/  Buffer; int /*<<< orphan*/  BufferOffset; void* AdditionalInformation; void* VolatileFileId; void* PersistentFileId; void* FileInfoClass; void* InfoType; TYPE_1__ sync_hdr; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct cifs_tcon {int /*<<< orphan*/  tid; struct cifs_ses* ses; } ;
struct cifs_ses {int /*<<< orphan*/  Suid; int /*<<< orphan*/  server; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int CIFS_TRANSFORM_REQ ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMB2_SET_INFO ; 
 int /*<<< orphan*/  SMB2_SET_INFO_HE ; 
 int /*<<< orphan*/  cifs_buf_release (struct smb2_set_info_req*) ; 
 int cifs_send_recv (unsigned int const,struct cifs_ses*,struct smb_rqst*,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_stats_fail_inc (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  free_rsp_buf (int,struct smb2_set_info_rsp*) ; 
 int /*<<< orphan*/  kfree (struct kvec*) ; 
 struct kvec* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (void**,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 
 scalar_t__ smb3_encryption_required (struct cifs_tcon*) ; 
 int /*<<< orphan*/  trace_smb3_set_info_err (unsigned int const,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
send_set_info(const unsigned int xid, struct cifs_tcon *tcon,
	       u64 persistent_fid, u64 volatile_fid, u32 pid, u8 info_class,
	       u8 info_type, u32 additional_info, unsigned int num,
		void **data, unsigned int *size)
{
	struct smb_rqst rqst;
	struct smb2_set_info_req *req;
	struct smb2_set_info_rsp *rsp = NULL;
	struct kvec *iov;
	struct kvec rsp_iov;
	int rc = 0;
	int resp_buftype;
	unsigned int i;
	struct cifs_ses *ses = tcon->ses;
	int flags = 0;
	unsigned int total_len;

	if (!ses || !(ses->server))
		return -EIO;

	if (!num)
		return -EINVAL;

	iov = kmalloc_array(num, sizeof(struct kvec), GFP_KERNEL);
	if (!iov)
		return -ENOMEM;

	rc = smb2_plain_req_init(SMB2_SET_INFO, tcon, (void **) &req, &total_len);
	if (rc) {
		kfree(iov);
		return rc;
	}

	if (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->sync_hdr.ProcessId = cpu_to_le32(pid);

	req->InfoType = info_type;
	req->FileInfoClass = info_class;
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = volatile_fid;
	req->AdditionalInformation = cpu_to_le32(additional_info);

	req->BufferOffset =
			cpu_to_le16(sizeof(struct smb2_set_info_req) - 1);
	req->BufferLength = cpu_to_le32(*size);

	memcpy(req->Buffer, *data, *size);
	total_len += *size;

	iov[0].iov_base = (char *)req;
	/* 1 for Buffer */
	iov[0].iov_len = total_len - 1;

	for (i = 1; i < num; i++) {
		le32_add_cpu(&req->BufferLength, size[i]);
		iov[i].iov_base = (char *)data[i];
		iov[i].iov_len = size[i];
	}

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = num;

	rc = cifs_send_recv(xid, ses, &rqst, &resp_buftype, flags,
			    &rsp_iov);
	cifs_buf_release(req);
	rsp = (struct smb2_set_info_rsp *)rsp_iov.iov_base;

	if (rc != 0) {
		cifs_stats_fail_inc(tcon, SMB2_SET_INFO_HE);
		trace_smb3_set_info_err(xid, persistent_fid, tcon->tid,
				ses->Suid, info_class, (__u32)info_type, rc);
	}

	free_rsp_buf(resp_buftype, rsp);
	kfree(iov);
	return rc;
}