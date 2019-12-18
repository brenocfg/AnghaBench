#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_ino_t ;
typedef  scalar_t__ uint16_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {int /*<<< orphan*/  m_dir_geo; TYPE_5__ m_sb; } ;
struct TYPE_8__ {void* magic; } ;
struct TYPE_9__ {TYPE_3__ info; } ;
struct TYPE_6__ {void* magic; } ;
struct TYPE_7__ {int /*<<< orphan*/  uuid; void* owner; void* blkno; TYPE_1__ hdr; } ;
struct xfs_dir3_leaf_hdr {TYPE_4__ hdr; TYPE_2__ info; } ;
struct xfs_dir2_leaf_tail {scalar_t__ bestcount; } ;
struct xfs_dir2_leaf {TYPE_4__ hdr; TYPE_2__ info; } ;
struct xfs_buf {int /*<<< orphan*/ * b_ops; int /*<<< orphan*/  b_bn; struct xfs_dir3_leaf_hdr* b_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_BLFT_DIR_LEAF1_BUF ; 
 int /*<<< orphan*/  XFS_BLFT_DIR_LEAFN_BUF ; 
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAFN_MAGIC ; 
 void* cpu_to_be16 (scalar_t__) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xfs_dir3_leaf_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xfs_dir2_leaf_tail* xfs_dir2_leaf_tail_p (int /*<<< orphan*/ ,struct xfs_dir3_leaf_hdr*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf1_buf_ops ; 
 int /*<<< orphan*/  xfs_dir3_leafn_buf_ops ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_dir3_leaf_init(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	struct xfs_buf		*bp,
	xfs_ino_t		owner,
	uint16_t		type)
{
	struct xfs_dir2_leaf	*leaf = bp->b_addr;

	ASSERT(type == XFS_DIR2_LEAF1_MAGIC || type == XFS_DIR2_LEAFN_MAGIC);

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_dir3_leaf_hdr *leaf3 = bp->b_addr;

		memset(leaf3, 0, sizeof(*leaf3));

		leaf3->info.hdr.magic = (type == XFS_DIR2_LEAF1_MAGIC)
					 ? cpu_to_be16(XFS_DIR3_LEAF1_MAGIC)
					 : cpu_to_be16(XFS_DIR3_LEAFN_MAGIC);
		leaf3->info.blkno = cpu_to_be64(bp->b_bn);
		leaf3->info.owner = cpu_to_be64(owner);
		uuid_copy(&leaf3->info.uuid, &mp->m_sb.sb_meta_uuid);
	} else {
		memset(leaf, 0, sizeof(*leaf));
		leaf->hdr.info.magic = cpu_to_be16(type);
	}

	/*
	 * If it's a leaf-format directory initialize the tail.
	 * Caller is responsible for initialising the bests table.
	 */
	if (type == XFS_DIR2_LEAF1_MAGIC) {
		struct xfs_dir2_leaf_tail *ltp;

		ltp = xfs_dir2_leaf_tail_p(mp->m_dir_geo, leaf);
		ltp->bestcount = 0;
		bp->b_ops = &xfs_dir3_leaf1_buf_ops;
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DIR_LEAF1_BUF);
	} else {
		bp->b_ops = &xfs_dir3_leafn_buf_ops;
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DIR_LEAFN_BUF);
	}
}