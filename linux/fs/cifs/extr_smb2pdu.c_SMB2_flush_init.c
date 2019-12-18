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
struct smb_rqst {struct kvec* rq_iov; } ;
struct smb2_flush_req {void* VolatileFileId; void* PersistentFileId; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct cifs_tcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_FLUSH ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 

int
SMB2_flush_init(const unsigned int xid, struct smb_rqst *rqst,
		struct cifs_tcon *tcon, u64 persistent_fid, u64 volatile_fid)
{
	struct smb2_flush_req *req;
	struct kvec *iov = rqst->rq_iov;
	unsigned int total_len;
	int rc;

	rc = smb2_plain_req_init(SMB2_FLUSH, tcon, (void **) &req, &total_len);
	if (rc)
		return rc;

	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = volatile_fid;

	iov[0].iov_base = (char *)req;
	iov[0].iov_len = total_len;

	return 0;
}