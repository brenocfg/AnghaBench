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
typedef  int /*<<< orphan*/  wchar_t ;
struct smb_rqst {unsigned int rq_nvec; struct kvec* rq_iov; } ;
struct TYPE_6__ {int /*<<< orphan*/  Flags; } ;
struct smb2_create_req {scalar_t__ RequestedOplockLevel; void* NameLength; TYPE_2__ sync_hdr; void* NameOffset; void* CreateOptions; void* CreateDisposition; int /*<<< orphan*/  ShareAccess; void* FileAttributes; void* DesiredAccess; int /*<<< orphan*/  ImpersonationLevel; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
struct create_context {void* Next; } ;
struct cifs_tcon {int share_flags; int /*<<< orphan*/  snapshot_time; scalar_t__ posix_extensions; int /*<<< orphan*/  use_persistent; scalar_t__ no_lease; int /*<<< orphan*/  treeName; TYPE_1__* ses; } ;
struct cifs_open_parms {int create_options; int desired_access; int disposition; int /*<<< orphan*/  mode; TYPE_3__* fid; } ;
struct TCP_Server_Info {int capabilities; TYPE_4__* vals; int /*<<< orphan*/  oplocks; } ;
typedef  scalar_t__ __u8 ;
typedef  int __u32 ;
typedef  char __le16 ;
struct TYPE_8__ {int create_lease_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  lease_key; } ;
struct TYPE_5__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_NO_MODE ; 
 int ATTR_READONLY ; 
 int ATTR_SYSTEM ; 
 int CREATE_NOT_FILE ; 
 int CREATE_OPTIONS_MASK ; 
 int CREATE_OPTION_READONLY ; 
 int CREATE_OPTION_SPECIAL ; 
 int ENOMEM ; 
 int FILE_CREATE ; 
 int /*<<< orphan*/  FILE_SHARE_ALL_LE ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IL_IMPERSONATION ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SHI1005_FLAGS_DFS ; 
 int /*<<< orphan*/  SMB2_CREATE ; 
 int /*<<< orphan*/  SMB2_FLAGS_DFS_OPERATIONS ; 
 int SMB2_GLOBAL_CAP_DIRECTORY_LEASING ; 
 int SMB2_GLOBAL_CAP_LEASING ; 
 scalar_t__ SMB2_OPLOCK_LEVEL_BATCH ; 
 scalar_t__ SMB2_OPLOCK_LEVEL_NONE ; 
 int UniStrnlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int add_durable_context (struct kvec*,unsigned int*,struct cifs_open_parms*,int /*<<< orphan*/ ) ; 
 int add_lease_context (struct TCP_Server_Info*,struct kvec*,unsigned int*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int add_posix_context (struct kvec*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_query_id_context (struct kvec*,unsigned int*) ; 
 int add_twarp_context (struct kvec*,unsigned int*,int /*<<< orphan*/ ) ; 
 int alloc_path_with_tree_prefix (char**,int*,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int roundup (int,int) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,struct cifs_tcon*,void**,unsigned int*) ; 

int
SMB2_open_init(struct cifs_tcon *tcon, struct smb_rqst *rqst, __u8 *oplock,
	       struct cifs_open_parms *oparms, __le16 *path)
{
	struct TCP_Server_Info *server = tcon->ses->server;
	struct smb2_create_req *req;
	unsigned int n_iov = 2;
	__u32 file_attributes = 0;
	int copy_size;
	int uni_path_len;
	unsigned int total_len;
	struct kvec *iov = rqst->rq_iov;
	__le16 *copy_path;
	int rc;

	rc = smb2_plain_req_init(SMB2_CREATE, tcon, (void **) &req, &total_len);
	if (rc)
		return rc;

	iov[0].iov_base = (char *)req;
	/* -1 since last byte is buf[0] which is sent below (path) */
	iov[0].iov_len = total_len - 1;

	if (oparms->create_options & CREATE_OPTION_READONLY)
		file_attributes |= ATTR_READONLY;
	if (oparms->create_options & CREATE_OPTION_SPECIAL)
		file_attributes |= ATTR_SYSTEM;

	req->ImpersonationLevel = IL_IMPERSONATION;
	req->DesiredAccess = cpu_to_le32(oparms->desired_access);
	/* File attributes ignored on open (used in create though) */
	req->FileAttributes = cpu_to_le32(file_attributes);
	req->ShareAccess = FILE_SHARE_ALL_LE;

	req->CreateDisposition = cpu_to_le32(oparms->disposition);
	req->CreateOptions = cpu_to_le32(oparms->create_options & CREATE_OPTIONS_MASK);
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
						 tcon->treeName, path);
		if (rc)
			return rc;
		req->NameLength = cpu_to_le16(name_len * 2);
		uni_path_len = copy_size;
		path = copy_path;
	} else {
		uni_path_len = (2 * UniStrnlen((wchar_t *)path, PATH_MAX)) + 2;
		/* MUST set path len (NameLength) to 0 opening root of share */
		req->NameLength = cpu_to_le16(uni_path_len - 2);
		copy_size = uni_path_len;
		if (copy_size % 8 != 0)
			copy_size = roundup(copy_size, 8);
		copy_path = kzalloc(copy_size, GFP_KERNEL);
		if (!copy_path)
			return -ENOMEM;
		memcpy((char *)copy_path, (const char *)path,
		       uni_path_len);
		uni_path_len = copy_size;
		path = copy_path;
	}

	iov[1].iov_len = uni_path_len;
	iov[1].iov_base = path;

	if ((!server->oplocks) || (tcon->no_lease))
		*oplock = SMB2_OPLOCK_LEVEL_NONE;

	if (!(server->capabilities & SMB2_GLOBAL_CAP_LEASING) ||
	    *oplock == SMB2_OPLOCK_LEVEL_NONE)
		req->RequestedOplockLevel = *oplock;
	else if (!(server->capabilities & SMB2_GLOBAL_CAP_DIRECTORY_LEASING) &&
		  (oparms->create_options & CREATE_NOT_FILE))
		req->RequestedOplockLevel = *oplock; /* no srv lease support */
	else {
		rc = add_lease_context(server, iov, &n_iov,
				       oparms->fid->lease_key, oplock);
		if (rc)
			return rc;
	}

	if (*oplock == SMB2_OPLOCK_LEVEL_BATCH) {
		/* need to set Next field of lease context if we request it */
		if (server->capabilities & SMB2_GLOBAL_CAP_LEASING) {
			struct create_context *ccontext =
			    (struct create_context *)iov[n_iov-1].iov_base;
			ccontext->Next =
				cpu_to_le32(server->vals->create_lease_size);
		}

		rc = add_durable_context(iov, &n_iov, oparms,
					tcon->use_persistent);
		if (rc)
			return rc;
	}

	if (tcon->posix_extensions) {
		if (n_iov > 2) {
			struct create_context *ccontext =
			    (struct create_context *)iov[n_iov-1].iov_base;
			ccontext->Next =
				cpu_to_le32(iov[n_iov-1].iov_len);
		}

		rc = add_posix_context(iov, &n_iov, oparms->mode);
		if (rc)
			return rc;
	}

	if (tcon->snapshot_time) {
		cifs_dbg(FYI, "adding snapshot context\n");
		if (n_iov > 2) {
			struct create_context *ccontext =
			    (struct create_context *)iov[n_iov-1].iov_base;
			ccontext->Next =
				cpu_to_le32(iov[n_iov-1].iov_len);
		}

		rc = add_twarp_context(iov, &n_iov, tcon->snapshot_time);
		if (rc)
			return rc;
	}

	if ((oparms->disposition == FILE_CREATE) &&
	    (oparms->mode != ACL_NO_MODE)) {
		if (n_iov > 2) {
			struct create_context *ccontext =
			    (struct create_context *)iov[n_iov-1].iov_base;
			ccontext->Next =
				cpu_to_le32(iov[n_iov-1].iov_len);
		}

		/* rc = add_sd_context(iov, &n_iov, oparms->mode); */
		if (rc)
			return rc;
	}

	if (n_iov > 2) {
		struct create_context *ccontext =
			(struct create_context *)iov[n_iov-1].iov_base;
		ccontext->Next = cpu_to_le32(iov[n_iov-1].iov_len);
	}
	add_query_id_context(iov, &n_iov);

	rqst->rq_nvec = n_iov;
	return 0;
}