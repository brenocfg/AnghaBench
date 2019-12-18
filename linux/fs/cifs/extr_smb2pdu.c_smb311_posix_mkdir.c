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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  umode_t ;
struct smb_rqst {unsigned int rq_nvec; struct kvec* rq_iov; } ;
struct smb2_create_rsp {int /*<<< orphan*/  VolatileFileId; int /*<<< orphan*/  PersistentFileId; } ;
struct TYPE_2__ {int /*<<< orphan*/  Flags; } ;
struct smb2_create_req {int /*<<< orphan*/  RequestedOplockLevel; void* NameLength; TYPE_1__ sync_hdr; void* NameOffset; void* CreateOptions; void* CreateDisposition; int /*<<< orphan*/  ShareAccess; void* FileAttributes; void* DesiredAccess; int /*<<< orphan*/  ImpersonationLevel; } ;
struct kvec {char* iov_base; unsigned int iov_len; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct inode {int dummy; } ;
struct cifs_tcon {int share_flags; int /*<<< orphan*/  tid; scalar_t__ posix_extensions; int /*<<< orphan*/  treeName; struct cifs_ses* ses; } ;
struct cifs_ses {int /*<<< orphan*/  Suid; int /*<<< orphan*/  server; } ;
struct cifs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  char __le16 ;

/* Variables and functions */
 int CIFS_TRANSFORM_REQ ; 
 int /*<<< orphan*/  CREATE_NOT_FILE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FILE_CREATE ; 
 int /*<<< orphan*/  FILE_SHARE_ALL_LE ; 
 int /*<<< orphan*/  FILE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IL_IMPERSONATION ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SHI1005_FLAGS_DFS ; 
 int /*<<< orphan*/  SMB2_CREATE ; 
 int /*<<< orphan*/  SMB2_CREATE_HE ; 
 int /*<<< orphan*/  SMB2_FLAGS_DFS_OPERATIONS ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_NONE ; 
 int /*<<< orphan*/  SMB2_close (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UniStrnlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int add_posix_context (struct kvec*,unsigned int*,int /*<<< orphan*/ ) ; 
 int alloc_path_with_tree_prefix (char**,int*,int*,int /*<<< orphan*/ ,char*) ; 
 char* cifs_convert_path_to_utf16 (char const*,struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int cifs_send_recv (unsigned int const,struct cifs_ses*,struct smb_rqst*,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb2_create_req*) ; 
 int /*<<< orphan*/  cifs_stats_fail_inc (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rsp_buf (int,struct smb2_create_rsp*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 
 int roundup (int,int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 
 scalar_t__ smb3_encryption_required (struct cifs_tcon*) ; 
 int /*<<< orphan*/  trace_smb3_posix_mkdir_done (unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_smb3_posix_mkdir_enter (unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_smb3_posix_mkdir_err (unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int smb311_posix_mkdir(const unsigned int xid, struct inode *inode,
			       umode_t mode, struct cifs_tcon *tcon,
			       const char *full_path,
			       struct cifs_sb_info *cifs_sb)
{
	struct smb_rqst rqst;
	struct smb2_create_req *req;
	struct smb2_create_rsp *rsp = NULL;
	struct cifs_ses *ses = tcon->ses;
	struct kvec iov[3]; /* make sure at least one for each open context */
	struct kvec rsp_iov = {NULL, 0};
	int resp_buftype;
	int uni_path_len;
	__le16 *copy_path = NULL;
	int copy_size;
	int rc = 0;
	unsigned int n_iov = 2;
	__u32 file_attributes = 0;
	char *pc_buf = NULL;
	int flags = 0;
	unsigned int total_len;
	__le16 *utf16_path = NULL;

	cifs_dbg(FYI, "mkdir\n");

	/* resource #1: path allocation */
	utf16_path = cifs_convert_path_to_utf16(full_path, cifs_sb);
	if (!utf16_path)
		return -ENOMEM;

	if (!ses || !(ses->server)) {
		rc = -EIO;
		goto err_free_path;
	}

	/* resource #2: request */
	rc = smb2_plain_req_init(SMB2_CREATE, tcon, (void **) &req, &total_len);
	if (rc)
		goto err_free_path;


	if (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req->ImpersonationLevel = IL_IMPERSONATION;
	req->DesiredAccess = cpu_to_le32(FILE_WRITE_ATTRIBUTES);
	/* File attributes ignored on open (used in create though) */
	req->FileAttributes = cpu_to_le32(file_attributes);
	req->ShareAccess = FILE_SHARE_ALL_LE;
	req->CreateDisposition = cpu_to_le32(FILE_CREATE);
	req->CreateOptions = cpu_to_le32(CREATE_NOT_FILE);

	iov[0].iov_base = (char *)req;
	/* -1 since last byte is buf[0] which is sent below (path) */
	iov[0].iov_len = total_len - 1;

	req->NameOffset = cpu_to_le16(sizeof(struct smb2_create_req));

	/* [MS-SMB2] 2.2.13 NameOffset:
	 * If SMB2_FLAGS_DFS_OPERATIONS is set in the Flags field of
	 * the SMB2 header, the file name includes a prefix that will
	 * be processed during DFS name normalization as specified in
	 * section 3.3.5.9. Otherwise, the file name is relative to
	 * the share that is identified by the TreeId in the SMB2
	 * header.
	 */
	if (tcon->share_flags & SHI1005_FLAGS_DFS) {
		int name_len;

		req->sync_hdr.Flags |= SMB2_FLAGS_DFS_OPERATIONS;
		rc = alloc_path_with_tree_prefix(&copy_path, &copy_size,
						 &name_len,
						 tcon->treeName, utf16_path);
		if (rc)
			goto err_free_req;

		req->NameLength = cpu_to_le16(name_len * 2);
		uni_path_len = copy_size;
		/* free before overwriting resource */
		kfree(utf16_path);
		utf16_path = copy_path;
	} else {
		uni_path_len = (2 * UniStrnlen((wchar_t *)utf16_path, PATH_MAX)) + 2;
		/* MUST set path len (NameLength) to 0 opening root of share */
		req->NameLength = cpu_to_le16(uni_path_len - 2);
		if (uni_path_len % 8 != 0) {
			copy_size = roundup(uni_path_len, 8);
			copy_path = kzalloc(copy_size, GFP_KERNEL);
			if (!copy_path) {
				rc = -ENOMEM;
				goto err_free_req;
			}
			memcpy((char *)copy_path, (const char *)utf16_path,
			       uni_path_len);
			uni_path_len = copy_size;
			/* free before overwriting resource */
			kfree(utf16_path);
			utf16_path = copy_path;
		}
	}

	iov[1].iov_len = uni_path_len;
	iov[1].iov_base = utf16_path;
	req->RequestedOplockLevel = SMB2_OPLOCK_LEVEL_NONE;

	if (tcon->posix_extensions) {
		/* resource #3: posix buf */
		rc = add_posix_context(iov, &n_iov, mode);
		if (rc)
			goto err_free_req;
		pc_buf = iov[n_iov-1].iov_base;
	}


	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = iov;
	rqst.rq_nvec = n_iov;

	/* no need to inc num_remote_opens because we close it just below */
	trace_smb3_posix_mkdir_enter(xid, tcon->tid, ses->Suid, CREATE_NOT_FILE,
				    FILE_WRITE_ATTRIBUTES);
	/* resource #4: response buffer */
	rc = cifs_send_recv(xid, ses, &rqst, &resp_buftype, flags, &rsp_iov);
	if (rc) {
		cifs_stats_fail_inc(tcon, SMB2_CREATE_HE);
		trace_smb3_posix_mkdir_err(xid, tcon->tid, ses->Suid,
					   CREATE_NOT_FILE,
					   FILE_WRITE_ATTRIBUTES, rc);
		goto err_free_rsp_buf;
	}

	rsp = (struct smb2_create_rsp *)rsp_iov.iov_base;
	trace_smb3_posix_mkdir_done(xid, rsp->PersistentFileId, tcon->tid,
				    ses->Suid, CREATE_NOT_FILE,
				    FILE_WRITE_ATTRIBUTES);

	SMB2_close(xid, tcon, rsp->PersistentFileId, rsp->VolatileFileId);

	/* Eventually save off posix specific response info and timestaps */

err_free_rsp_buf:
	free_rsp_buf(resp_buftype, rsp);
	kfree(pc_buf);
err_free_req:
	cifs_small_buf_release(req);
err_free_path:
	kfree(utf16_path);
	return rc;
}