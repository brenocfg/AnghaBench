#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_failaddr_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_6__ m_sb; } ;
struct TYPE_10__ {scalar_t__ magic; } ;
struct TYPE_11__ {TYPE_4__ info; } ;
struct TYPE_8__ {scalar_t__ magic; } ;
struct TYPE_9__ {int /*<<< orphan*/  lsn; int /*<<< orphan*/  blkno; int /*<<< orphan*/  uuid; TYPE_2__ hdr; } ;
struct xfs_dir3_leaf_hdr {TYPE_5__ hdr; TYPE_3__ info; } ;
struct xfs_dir2_leaf {TYPE_5__ hdr; TYPE_3__ info; } ;
struct xfs_buf {scalar_t__ b_bn; struct xfs_dir3_leaf_hdr* b_addr; TYPE_1__* b_target; } ;
struct TYPE_7__ {struct xfs_mount* bt_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAFN_MAGIC ; 
 int /*<<< orphan*/  __this_address ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check_int (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct xfs_dir3_leaf_hdr*) ; 
 int /*<<< orphan*/  xfs_log_check_lsn (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_6__*) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_dir3_leaf_verify(
	struct xfs_buf		*bp,
	uint16_t		magic)
{
	struct xfs_mount	*mp = bp->b_target->bt_mount;
	struct xfs_dir2_leaf	*leaf = bp->b_addr;

	ASSERT(magic == XFS_DIR2_LEAF1_MAGIC || magic == XFS_DIR2_LEAFN_MAGIC);

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_dir3_leaf_hdr *leaf3 = bp->b_addr;
		uint16_t		magic3;

		magic3 = (magic == XFS_DIR2_LEAF1_MAGIC) ? XFS_DIR3_LEAF1_MAGIC
							 : XFS_DIR3_LEAFN_MAGIC;

		if (leaf3->info.hdr.magic != cpu_to_be16(magic3))
			return __this_address;
		if (!uuid_equal(&leaf3->info.uuid, &mp->m_sb.sb_meta_uuid))
			return __this_address;
		if (be64_to_cpu(leaf3->info.blkno) != bp->b_bn)
			return __this_address;
		if (!xfs_log_check_lsn(mp, be64_to_cpu(leaf3->info.lsn)))
			return __this_address;
	} else {
		if (leaf->hdr.info.magic != cpu_to_be16(magic))
			return __this_address;
	}

	return xfs_dir3_leaf_check_int(mp, NULL, NULL, leaf);
}