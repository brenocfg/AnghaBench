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
typedef  void* u64 ;
struct smb2_query_info_rsp {int dummy; } ;
struct smb2_query_info_req {int FileInfoClass; int /*<<< orphan*/  OutputBufferLength; int /*<<< orphan*/  InputBufferOffset; void* VolatileFileId; void* PersistentFileId; int /*<<< orphan*/  InfoType; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct cifs_tcon {TYPE_1__* ses; } ;
struct TYPE_2__ {int /*<<< orphan*/ * server; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB2_O_INFO_FILESYSTEM ; 
 int /*<<< orphan*/  SMB2_QUERY_INFO ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 

__attribute__((used)) static int
build_qfs_info_req(struct kvec *iov, struct cifs_tcon *tcon, int level,
		   int outbuf_len, u64 persistent_fid, u64 volatile_fid)
{
	int rc;
	struct smb2_query_info_req *req;
	unsigned int total_len;

	cifs_dbg(FYI, "Query FSInfo level %d\n", level);

	if ((tcon->ses == NULL) || (tcon->ses->server == NULL))
		return -EIO;

	rc = smb2_plain_req_init(SMB2_QUERY_INFO, tcon, (void **) &req,
			     &total_len);
	if (rc)
		return rc;

	req->InfoType = SMB2_O_INFO_FILESYSTEM;
	req->FileInfoClass = level;
	req->PersistentFileId = persistent_fid;
	req->VolatileFileId = volatile_fid;
	/* 1 for pad */
	req->InputBufferOffset =
			cpu_to_le16(sizeof(struct smb2_query_info_req) - 1);
	req->OutputBufferLength = cpu_to_le32(
		outbuf_len + sizeof(struct smb2_query_info_rsp) - 1);

	iov->iov_base = (char *)req;
	iov->iov_len = total_len;
	return 0;
}