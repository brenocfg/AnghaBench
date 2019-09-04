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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct afs_xdr_AFSFetchStatus {scalar_t__ abort_code; scalar_t__ if_version; scalar_t__ type; scalar_t__ nlink; scalar_t__ author; scalar_t__ owner; scalar_t__ caller_access; scalar_t__ anon_access; scalar_t__ mode; scalar_t__ group; scalar_t__ mtime_client; scalar_t__ mtime_server; scalar_t__ lock_count; scalar_t__ size_lo; scalar_t__ size_hi; scalar_t__ data_version_lo; scalar_t__ data_version_hi; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  flags; TYPE_1__ fid; } ;
struct afs_read {int data_version; int file_size; } ;
struct afs_file_status {scalar_t__ type; scalar_t__ nlink; scalar_t__ author; scalar_t__ owner; scalar_t__ caller_access; scalar_t__ anon_access; scalar_t__ mode; scalar_t__ group; int size; int data_version; scalar_t__ lock_count; scalar_t__ mtime_server; scalar_t__ mtime_client; scalar_t__ abort_code; } ;
struct afs_call {scalar_t__ operation_ID; } ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_FSTATUS_VERSION ; 
#define  AFS_FTYPE_DIR 130 
#define  AFS_FTYPE_FILE 129 
#define  AFS_FTYPE_SYMLINK 128 
 int /*<<< orphan*/  AFS_VNODE_DATA_CHANGED ; 
 int /*<<< orphan*/  AFS_VNODE_META_CHANGED ; 
 int /*<<< orphan*/  AFS_VNODE_NOT_YET_SET ; 
 int /*<<< orphan*/  AFS_VNODE_UNSET ; 
 int /*<<< orphan*/  EBADMSG ; 
 scalar_t__ afs_FS_InlineBulkStatus ; 
 int afs_protocol_error (struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_update_inode_from_status (struct afs_vnode*,struct afs_file_status*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_dump_bad (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int xdr_decode_AFSFetchStatus(struct afs_call *call,
				     const __be32 **_bp,
				     struct afs_file_status *status,
				     struct afs_vnode *vnode,
				     const afs_dataversion_t *expected_version,
				     struct afs_read *read_req)
{
	const struct afs_xdr_AFSFetchStatus *xdr = (const void *)*_bp;
	bool inline_error = (call->operation_ID == afs_FS_InlineBulkStatus);
	u64 data_version, size;
	u32 type, abort_code;
	u8 flags = 0;

	abort_code = ntohl(xdr->abort_code);

	if (xdr->if_version != htonl(AFS_FSTATUS_VERSION)) {
		if (xdr->if_version == htonl(0) &&
		    abort_code != 0 &&
		    inline_error) {
			/* The OpenAFS fileserver has a bug in FS.InlineBulkStatus
			 * whereby it doesn't set the interface version in the error
			 * case.
			 */
			status->abort_code = abort_code;
			return 0;
		}

		pr_warn("Unknown AFSFetchStatus version %u\n", ntohl(xdr->if_version));
		goto bad;
	}

	if (abort_code != 0 && inline_error) {
		status->abort_code = abort_code;
		return 0;
	}

	type = ntohl(xdr->type);
	switch (type) {
	case AFS_FTYPE_FILE:
	case AFS_FTYPE_DIR:
	case AFS_FTYPE_SYMLINK:
		if (type != status->type &&
		    vnode &&
		    !test_bit(AFS_VNODE_UNSET, &vnode->flags)) {
			pr_warning("Vnode %x:%x:%x changed type %u to %u\n",
				   vnode->fid.vid,
				   vnode->fid.vnode,
				   vnode->fid.unique,
				   status->type, type);
			goto bad;
		}
		status->type = type;
		break;
	default:
		goto bad;
	}

#define EXTRACT_M(FIELD)					\
	do {							\
		u32 x = ntohl(xdr->FIELD);			\
		if (status->FIELD != x) {			\
			flags |= AFS_VNODE_META_CHANGED;	\
			status->FIELD = x;			\
		}						\
	} while (0)

	EXTRACT_M(nlink);
	EXTRACT_M(author);
	EXTRACT_M(owner);
	EXTRACT_M(caller_access); /* call ticket dependent */
	EXTRACT_M(anon_access);
	EXTRACT_M(mode);
	EXTRACT_M(group);

	status->mtime_client = ntohl(xdr->mtime_client);
	status->mtime_server = ntohl(xdr->mtime_server);
	status->lock_count   = ntohl(xdr->lock_count);

	size  = (u64)ntohl(xdr->size_lo);
	size |= (u64)ntohl(xdr->size_hi) << 32;
	status->size = size;

	data_version  = (u64)ntohl(xdr->data_version_lo);
	data_version |= (u64)ntohl(xdr->data_version_hi) << 32;
	if (data_version != status->data_version) {
		status->data_version = data_version;
		flags |= AFS_VNODE_DATA_CHANGED;
	}

	if (read_req) {
		read_req->data_version = data_version;
		read_req->file_size = size;
	}

	*_bp = (const void *)*_bp + sizeof(*xdr);

	if (vnode) {
		if (test_bit(AFS_VNODE_UNSET, &vnode->flags))
			flags |= AFS_VNODE_NOT_YET_SET;
		afs_update_inode_from_status(vnode, status, expected_version,
					     flags);
	}

	return 0;

bad:
	xdr_dump_bad(*_bp);
	return afs_protocol_error(call, -EBADMSG);
}