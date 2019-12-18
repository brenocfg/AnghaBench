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
struct xfs_dir2_data_free {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
typedef  struct xfs_dir2_data_free xfs_dir2_data_free_t ;
struct xfs_dir2_data_unused {int /*<<< orphan*/  length; } ;
struct xfs_dir2_data_hdr {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DIR2_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 

xfs_dir2_data_free_t *				/* entry inserted */
xfs_dir2_data_freeinsert(
	struct xfs_dir2_data_hdr *hdr,		/* data block pointer */
	struct xfs_dir2_data_free *dfp,		/* bestfree table pointer */
	struct xfs_dir2_data_unused *dup,	/* unused space */
	int			*loghead)	/* log the data header (out) */
{
	xfs_dir2_data_free_t	new;		/* new bestfree entry */

	ASSERT(hdr->magic == cpu_to_be32(XFS_DIR2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_BLOCK_MAGIC));

	new.length = dup->length;
	new.offset = cpu_to_be16((char *)dup - (char *)hdr);

	/*
	 * Insert at position 0, 1, or 2; or not at all.
	 */
	if (be16_to_cpu(new.length) > be16_to_cpu(dfp[0].length)) {
		dfp[2] = dfp[1];
		dfp[1] = dfp[0];
		dfp[0] = new;
		*loghead = 1;
		return &dfp[0];
	}
	if (be16_to_cpu(new.length) > be16_to_cpu(dfp[1].length)) {
		dfp[2] = dfp[1];
		dfp[1] = new;
		*loghead = 1;
		return &dfp[1];
	}
	if (be16_to_cpu(new.length) > be16_to_cpu(dfp[2].length)) {
		dfp[2] = new;
		*loghead = 1;
		return &dfp[2];
	}
	return NULL;
}