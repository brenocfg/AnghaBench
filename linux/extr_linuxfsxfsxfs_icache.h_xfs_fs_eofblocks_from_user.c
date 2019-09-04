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
struct xfs_fs_eofblocks {scalar_t__ eof_version; int eof_flags; int /*<<< orphan*/  eof_gid; int /*<<< orphan*/  eof_uid; int /*<<< orphan*/  eof_min_file_size; int /*<<< orphan*/  eof_prid; int /*<<< orphan*/ * pad64; int /*<<< orphan*/  pad32; } ;
struct xfs_eofblocks {int eof_flags; int /*<<< orphan*/  eof_gid; int /*<<< orphan*/  eof_uid; int /*<<< orphan*/  eof_min_file_size; int /*<<< orphan*/  eof_prid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INVALID_GID ; 
 int /*<<< orphan*/  INVALID_UID ; 
 scalar_t__ XFS_EOFBLOCKS_VERSION ; 
 int XFS_EOF_FLAGS_GID ; 
 int XFS_EOF_FLAGS_UID ; 
 int XFS_EOF_FLAGS_VALID ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr_inv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
xfs_fs_eofblocks_from_user(
	struct xfs_fs_eofblocks		*src,
	struct xfs_eofblocks		*dst)
{
	if (src->eof_version != XFS_EOFBLOCKS_VERSION)
		return -EINVAL;

	if (src->eof_flags & ~XFS_EOF_FLAGS_VALID)
		return -EINVAL;

	if (memchr_inv(&src->pad32, 0, sizeof(src->pad32)) ||
	    memchr_inv(src->pad64, 0, sizeof(src->pad64)))
		return -EINVAL;

	dst->eof_flags = src->eof_flags;
	dst->eof_prid = src->eof_prid;
	dst->eof_min_file_size = src->eof_min_file_size;

	dst->eof_uid = INVALID_UID;
	if (src->eof_flags & XFS_EOF_FLAGS_UID) {
		dst->eof_uid = make_kuid(current_user_ns(), src->eof_uid);
		if (!uid_valid(dst->eof_uid))
			return -EINVAL;
	}

	dst->eof_gid = INVALID_GID;
	if (src->eof_flags & XFS_EOF_FLAGS_GID) {
		dst->eof_gid = make_kgid(current_user_ns(), src->eof_gid);
		if (!gid_valid(dst->eof_gid))
			return -EINVAL;
	}
	return 0;
}