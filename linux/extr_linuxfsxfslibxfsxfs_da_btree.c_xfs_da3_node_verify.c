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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct TYPE_10__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_4__* m_attr_geo; TYPE_3__* m_dir_geo; TYPE_5__ m_sb; } ;
struct xfs_dir_ops {int /*<<< orphan*/  (* node_hdr_from_disk ) (struct xfs_da3_icnode_hdr*,struct xfs_da_intnode*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  lsn; int /*<<< orphan*/  blkno; int /*<<< orphan*/  uuid; } ;
struct xfs_da_intnode {TYPE_2__ info; } ;
struct xfs_da3_node_hdr {TYPE_2__ info; } ;
struct xfs_da3_icnode_hdr {scalar_t__ magic; scalar_t__ level; scalar_t__ count; } ;
struct xfs_buf {scalar_t__ b_bn; struct xfs_da_intnode* b_addr; TYPE_1__* b_target; } ;
struct TYPE_9__ {scalar_t__ node_ents; } ;
struct TYPE_8__ {scalar_t__ node_ents; } ;
struct TYPE_6__ {struct xfs_mount* bt_mount; } ;

/* Variables and functions */
 scalar_t__ XFS_DA3_NODE_MAGIC ; 
 scalar_t__ XFS_DA_NODE_MAGIC ; 
 scalar_t__ XFS_DA_NODE_MAXDEPTH ; 
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_da3_icnode_hdr*,struct xfs_da_intnode*) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xfs_dir_ops* xfs_dir_get_ops (struct xfs_mount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_check_lsn (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_5__*) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_da3_node_verify(
	struct xfs_buf		*bp)
{
	struct xfs_mount	*mp = bp->b_target->bt_mount;
	struct xfs_da_intnode	*hdr = bp->b_addr;
	struct xfs_da3_icnode_hdr ichdr;
	const struct xfs_dir_ops *ops;

	ops = xfs_dir_get_ops(mp, NULL);

	ops->node_hdr_from_disk(&ichdr, hdr);

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_da3_node_hdr *hdr3 = bp->b_addr;

		if (ichdr.magic != XFS_DA3_NODE_MAGIC)
			return __this_address;

		if (!uuid_equal(&hdr3->info.uuid, &mp->m_sb.sb_meta_uuid))
			return __this_address;
		if (be64_to_cpu(hdr3->info.blkno) != bp->b_bn)
			return __this_address;
		if (!xfs_log_check_lsn(mp, be64_to_cpu(hdr3->info.lsn)))
			return __this_address;
	} else {
		if (ichdr.magic != XFS_DA_NODE_MAGIC)
			return __this_address;
	}
	if (ichdr.level == 0)
		return __this_address;
	if (ichdr.level > XFS_DA_NODE_MAXDEPTH)
		return __this_address;
	if (ichdr.count == 0)
		return __this_address;

	/*
	 * we don't know if the node is for and attribute or directory tree,
	 * so only fail if the count is outside both bounds
	 */
	if (ichdr.count > mp->m_dir_geo->node_ents &&
	    ichdr.count > mp->m_attr_geo->node_ents)
		return __this_address;

	/* XXX: hash order check? */

	return NULL;
}