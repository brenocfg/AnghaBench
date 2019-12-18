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
struct TYPE_2__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; } ;
struct xfs_dir3_blk_hdr {void* magic; int /*<<< orphan*/  uuid; void* owner; void* blkno; } ;
struct xfs_buf {int /*<<< orphan*/  b_bn; int /*<<< orphan*/ * b_ops; struct xfs_dir3_blk_hdr* b_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BLFT_DIR_BLOCK_BUF ; 
 int /*<<< orphan*/  XFS_DIR2_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_BLOCK_MAGIC ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xfs_dir3_blk_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir3_block_buf_ops ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir3_block_init(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	struct xfs_buf		*bp,
	struct xfs_inode	*dp)
{
	struct xfs_dir3_blk_hdr *hdr3 = bp->b_addr;

	bp->b_ops = &xfs_dir3_block_buf_ops;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DIR_BLOCK_BUF);

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		memset(hdr3, 0, sizeof(*hdr3));
		hdr3->magic = cpu_to_be32(XFS_DIR3_BLOCK_MAGIC);
		hdr3->blkno = cpu_to_be64(bp->b_bn);
		hdr3->owner = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdr3->uuid, &mp->m_sb.sb_meta_uuid);
		return;

	}
	hdr3->magic = cpu_to_be32(XFS_DIR2_BLOCK_MAGIC);
}