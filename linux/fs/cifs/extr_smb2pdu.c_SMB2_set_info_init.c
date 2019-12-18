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
struct TYPE_2__ {void* ProcessId; } ;
struct smb2_set_info_req {void* BufferLength; int /*<<< orphan*/  Buffer; int /*<<< orphan*/  BufferOffset; void* AdditionalInformation; void* VolatileFileId; void* PersistentFileId; void* FileInfoClass; void* InfoType; TYPE_1__ sync_hdr; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct cifs_tcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_SET_INFO ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  le32_add_cpu (void**,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 

int
SMB2_set_info_init(struct cifs_tcon *tcon, struct smb_rqst *rqst,
	       u64 persistent_fid, u64 volatile_fid, u32 pid, u8 info_class,
	       u8 info_type, u32 additional_info,
		void **data, unsigned int *size)
{
	struct smb2_set_info_req *req;
	struct kvec *iov = rqst->rq_iov;
	unsigned int i, total_len;
	int rc;

	rc = smb2_plain_req_init(SMB2_SET_INFO, tcon, (void **) &req, &total_len);
	if (rc)
		return rc;

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

	for (i = 1; i < rqst->rq_nvec; i++) {
		le32_add_cpu(&req->BufferLength, size[i]);
		iov[i].iov_base = (char *)data[i];
		iov[i].iov_len = size[i];
	}

	return 0;
}