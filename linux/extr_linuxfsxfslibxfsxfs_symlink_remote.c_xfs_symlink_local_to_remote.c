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
struct xfs_trans {int dummy; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_data; } ;
struct xfs_ifork {int /*<<< orphan*/  if_bytes; TYPE_1__ if_u1; } ;
struct xfs_dsymlink_hdr {int dummy; } ;
struct xfs_buf {char* b_addr; int /*<<< orphan*/ * b_ops; int /*<<< orphan*/  b_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BBTOB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_BLFT_SYMLINK_BUF ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_symlink_buf_ops ; 
 int /*<<< orphan*/  xfs_symlink_hdr_set (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ,scalar_t__) ; 

void
xfs_symlink_local_to_remote(
	struct xfs_trans	*tp,
	struct xfs_buf		*bp,
	struct xfs_inode	*ip,
	struct xfs_ifork	*ifp)
{
	struct xfs_mount	*mp = ip->i_mount;
	char			*buf;

	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_SYMLINK_BUF);

	if (!xfs_sb_version_hascrc(&mp->m_sb)) {
		bp->b_ops = NULL;
		memcpy(bp->b_addr, ifp->if_u1.if_data, ifp->if_bytes);
		xfs_trans_log_buf(tp, bp, 0, ifp->if_bytes - 1);
		return;
	}

	/*
	 * As this symlink fits in an inode literal area, it must also fit in
	 * the smallest buffer the filesystem supports.
	 */
	ASSERT(BBTOB(bp->b_length) >=
			ifp->if_bytes + sizeof(struct xfs_dsymlink_hdr));

	bp->b_ops = &xfs_symlink_buf_ops;

	buf = bp->b_addr;
	buf += xfs_symlink_hdr_set(mp, ip->i_ino, 0, ifp->if_bytes, bp);
	memcpy(buf, ifp->if_u1.if_data, ifp->if_bytes);
	xfs_trans_log_buf(tp, bp, 0, sizeof(struct xfs_dsymlink_hdr) +
					ifp->if_bytes - 1);
}