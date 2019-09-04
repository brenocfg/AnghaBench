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
typedef  int /*<<< orphan*/  xfs_dir2_leaf_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct xfs_dir3_leaf_hdr {int dummy; } ;
struct xfs_dir3_icleaf_hdr {int count; int stale; scalar_t__ magic; } ;
struct xfs_dir2_leaf_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 

__attribute__((used)) static inline size_t
xfs_dir3_leaf_size(
	struct xfs_dir3_icleaf_hdr	*hdr,
	int				counts)
{
	int	entries;
	int	hdrsize;

	entries = hdr->count - hdr->stale;
	if (hdr->magic == XFS_DIR2_LEAF1_MAGIC ||
	    hdr->magic == XFS_DIR2_LEAFN_MAGIC)
		hdrsize = sizeof(struct xfs_dir2_leaf_hdr);
	else
		hdrsize = sizeof(struct xfs_dir3_leaf_hdr);

	return hdrsize + entries * sizeof(xfs_dir2_leaf_entry_t)
	               + counts * sizeof(xfs_dir2_data_off_t)
		       + sizeof(xfs_dir2_leaf_tail_t);
}