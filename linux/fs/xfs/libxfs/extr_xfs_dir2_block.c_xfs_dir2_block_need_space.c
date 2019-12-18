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
struct xfs_dir2_data_unused {int /*<<< orphan*/  length; int /*<<< orphan*/  freetag; } ;
typedef  struct xfs_dir2_data_unused xfs_dir2_data_unused_t ;
typedef  int uint ;
struct xfs_inode {TYPE_1__* d_ops; } ;
struct xfs_dir2_leaf_entry {int dummy; } ;
struct xfs_dir2_data_hdr {int dummy; } ;
struct xfs_dir2_data_free {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
struct xfs_dir2_block_tail {scalar_t__ stale; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {struct xfs_dir2_data_free* (* data_bestfree_p ) (struct xfs_dir2_data_hdr*) ;} ;

/* Variables and functions */
 int XFS_DIR2_DATA_FREE_TAG ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (scalar_t__) ; 
 struct xfs_dir2_data_free* stub1 (struct xfs_dir2_data_hdr*) ; 

__attribute__((used)) static void
xfs_dir2_block_need_space(
	struct xfs_inode		*dp,
	struct xfs_dir2_data_hdr	*hdr,
	struct xfs_dir2_block_tail	*btp,
	struct xfs_dir2_leaf_entry	*blp,
	__be16				**tagpp,
	struct xfs_dir2_data_unused	**dupp,
	struct xfs_dir2_data_unused	**enddupp,
	int				*compact,
	int				len)
{
	struct xfs_dir2_data_free	*bf;
	__be16				*tagp = NULL;
	struct xfs_dir2_data_unused	*dup = NULL;
	struct xfs_dir2_data_unused	*enddup = NULL;

	*compact = 0;
	bf = dp->d_ops->data_bestfree_p(hdr);

	/*
	 * If there are stale entries we'll use one for the leaf.
	 */
	if (btp->stale) {
		if (be16_to_cpu(bf[0].length) >= len) {
			/*
			 * The biggest entry enough to avoid compaction.
			 */
			dup = (xfs_dir2_data_unused_t *)
			      ((char *)hdr + be16_to_cpu(bf[0].offset));
			goto out;
		}

		/*
		 * Will need to compact to make this work.
		 * Tag just before the first leaf entry.
		 */
		*compact = 1;
		tagp = (__be16 *)blp - 1;

		/* Data object just before the first leaf entry.  */
		dup = (xfs_dir2_data_unused_t *)((char *)hdr + be16_to_cpu(*tagp));

		/*
		 * If it's not free then the data will go where the
		 * leaf data starts now, if it works at all.
		 */
		if (be16_to_cpu(dup->freetag) == XFS_DIR2_DATA_FREE_TAG) {
			if (be16_to_cpu(dup->length) + (be32_to_cpu(btp->stale) - 1) *
			    (uint)sizeof(*blp) < len)
				dup = NULL;
		} else if ((be32_to_cpu(btp->stale) - 1) * (uint)sizeof(*blp) < len)
			dup = NULL;
		else
			dup = (xfs_dir2_data_unused_t *)blp;
		goto out;
	}

	/*
	 * no stale entries, so just use free space.
	 * Tag just before the first leaf entry.
	 */
	tagp = (__be16 *)blp - 1;

	/* Data object just before the first leaf entry.  */
	enddup = (xfs_dir2_data_unused_t *)((char *)hdr + be16_to_cpu(*tagp));

	/*
	 * If it's not free then can't do this add without cleaning up:
	 * the space before the first leaf entry needs to be free so it
	 * can be expanded to hold the pointer to the new entry.
	 */
	if (be16_to_cpu(enddup->freetag) == XFS_DIR2_DATA_FREE_TAG) {
		/*
		 * Check out the biggest freespace and see if it's the same one.
		 */
		dup = (xfs_dir2_data_unused_t *)
		      ((char *)hdr + be16_to_cpu(bf[0].offset));
		if (dup != enddup) {
			/*
			 * Not the same free entry, just check its length.
			 */
			if (be16_to_cpu(dup->length) < len)
				dup = NULL;
			goto out;
		}

		/*
		 * It is the biggest freespace, can it hold the leaf too?
		 */
		if (be16_to_cpu(dup->length) < len + (uint)sizeof(*blp)) {
			/*
			 * Yes, use the second-largest entry instead if it works.
			 */
			if (be16_to_cpu(bf[1].length) >= len)
				dup = (xfs_dir2_data_unused_t *)
				      ((char *)hdr + be16_to_cpu(bf[1].offset));
			else
				dup = NULL;
		}
	}
out:
	*tagpp = tagp;
	*dupp = dup;
	*enddupp = enddup;
}