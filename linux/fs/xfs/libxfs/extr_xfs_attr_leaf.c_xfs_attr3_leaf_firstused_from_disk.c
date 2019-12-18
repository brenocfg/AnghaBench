#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_da_geometry {scalar_t__ blksize; } ;
struct TYPE_3__ {scalar_t__ magic; } ;
struct TYPE_4__ {int /*<<< orphan*/  firstused; TYPE_1__ info; } ;
struct xfs_attr_leafblock {TYPE_2__ hdr; } ;
struct xfs_attr3_leaf_hdr {int /*<<< orphan*/  firstused; } ;
struct xfs_attr3_icleaf_hdr {scalar_t__ firstused; int /*<<< orphan*/  usedbytes; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  XFS_ATTR3_LEAF_MAGIC ; 
 scalar_t__ XFS_ATTR3_LEAF_NULLOFF ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_attr3_leaf_firstused_from_disk(
	struct xfs_da_geometry		*geo,
	struct xfs_attr3_icleaf_hdr	*to,
	struct xfs_attr_leafblock	*from)
{
	struct xfs_attr3_leaf_hdr	*hdr3;

	if (from->hdr.info.magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC)) {
		hdr3 = (struct xfs_attr3_leaf_hdr *) from;
		to->firstused = be16_to_cpu(hdr3->firstused);
	} else {
		to->firstused = be16_to_cpu(from->hdr.firstused);
	}

	/*
	 * Convert from the magic fsb size value to actual blocksize. This
	 * should only occur for empty blocks when the block size overflows
	 * 16-bits.
	 */
	if (to->firstused == XFS_ATTR3_LEAF_NULLOFF) {
		ASSERT(!to->count && !to->usedbytes);
		ASSERT(geo->blksize > USHRT_MAX);
		to->firstused = geo->blksize;
	}
}