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
struct xfs_dir2_data_free {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
typedef  struct xfs_dir2_data_free xfs_dir2_data_free_t ;
typedef  scalar_t__ xfs_dir2_data_aoff_t ;
struct xfs_dir2_data_unused {int /*<<< orphan*/  length; } ;
struct xfs_dir2_data_hdr {int dummy; } ;

/* Variables and functions */
 int XFS_DIR2_DATA_FD_COUNT ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 

xfs_dir2_data_free_t *
xfs_dir2_data_freefind(
	struct xfs_dir2_data_hdr *hdr,		/* data block header */
	struct xfs_dir2_data_free *bf,		/* bestfree table pointer */
	struct xfs_dir2_data_unused *dup)	/* unused space */
{
	xfs_dir2_data_free_t	*dfp;		/* bestfree entry */
	xfs_dir2_data_aoff_t	off;		/* offset value needed */

	off = (xfs_dir2_data_aoff_t)((char *)dup - (char *)hdr);

	/*
	 * If this is smaller than the smallest bestfree entry,
	 * it can't be there since they're sorted.
	 */
	if (be16_to_cpu(dup->length) <
	    be16_to_cpu(bf[XFS_DIR2_DATA_FD_COUNT - 1].length))
		return NULL;
	/*
	 * Look at the three bestfree entries for our guy.
	 */
	for (dfp = &bf[0]; dfp < &bf[XFS_DIR2_DATA_FD_COUNT]; dfp++) {
		if (!dfp->offset)
			return NULL;
		if (be16_to_cpu(dfp->offset) == off)
			return dfp;
	}
	/*
	 * Didn't find it.  This only happens if there are duplicate lengths.
	 */
	return NULL;
}