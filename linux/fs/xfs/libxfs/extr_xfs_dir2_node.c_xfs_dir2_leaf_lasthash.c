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
typedef  int /*<<< orphan*/  xfs_dahash_t ;
struct xfs_inode {TYPE_1__* d_ops; } ;
struct xfs_dir3_icleaf_hdr {scalar_t__ magic; int count; } ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  hashval; } ;
struct xfs_dir2_leaf {int dummy; } ;
struct xfs_buf {struct xfs_dir2_leaf* b_addr; } ;
struct TYPE_2__ {struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (struct xfs_dir2_leaf*) ;int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAFN_MAGIC ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf*) ; 
 struct xfs_dir2_leaf_entry* stub2 (struct xfs_dir2_leaf*) ; 

xfs_dahash_t					/* hash value */
xfs_dir2_leaf_lasthash(
	struct xfs_inode *dp,
	struct xfs_buf	*bp,			/* leaf buffer */
	int		*count)			/* count of entries in leaf */
{
	struct xfs_dir2_leaf	*leaf = bp->b_addr;
	struct xfs_dir2_leaf_entry *ents;
	struct xfs_dir3_icleaf_hdr leafhdr;

	dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);

	ASSERT(leafhdr.magic == XFS_DIR2_LEAFN_MAGIC ||
	       leafhdr.magic == XFS_DIR3_LEAFN_MAGIC ||
	       leafhdr.magic == XFS_DIR2_LEAF1_MAGIC ||
	       leafhdr.magic == XFS_DIR3_LEAF1_MAGIC);

	if (count)
		*count = leafhdr.count;
	if (!leafhdr.count)
		return 0;

	ents = dp->d_ops->leaf_ents_p(leaf);
	return be32_to_cpu(ents[leafhdr.count - 1].hashval);
}