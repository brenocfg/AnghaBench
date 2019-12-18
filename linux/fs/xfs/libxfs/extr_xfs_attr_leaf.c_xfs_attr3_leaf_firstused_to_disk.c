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
typedef  scalar_t__ uint32_t ;
struct xfs_da_geometry {scalar_t__ blksize; } ;
struct TYPE_2__ {void* firstused; } ;
struct xfs_attr_leafblock {TYPE_1__ hdr; } ;
struct xfs_attr3_leaf_hdr {void* firstused; } ;
struct xfs_attr3_icleaf_hdr {scalar_t__ firstused; scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ USHRT_MAX ; 
 scalar_t__ XFS_ATTR3_LEAF_MAGIC ; 
 scalar_t__ XFS_ATTR3_LEAF_NULLOFF ; 
 void* cpu_to_be16 (scalar_t__) ; 

__attribute__((used)) static void
xfs_attr3_leaf_firstused_to_disk(
	struct xfs_da_geometry		*geo,
	struct xfs_attr_leafblock	*to,
	struct xfs_attr3_icleaf_hdr	*from)
{
	struct xfs_attr3_leaf_hdr	*hdr3;
	uint32_t			firstused;

	/* magic value should only be seen on disk */
	ASSERT(from->firstused != XFS_ATTR3_LEAF_NULLOFF);

	/*
	 * Scale down the 32-bit in-core firstused value to the 16-bit on-disk
	 * value. This only overflows at the max supported value of 64k. Use the
	 * magic on-disk value to represent block size in this case.
	 */
	firstused = from->firstused;
	if (firstused > USHRT_MAX) {
		ASSERT(from->firstused == geo->blksize);
		firstused = XFS_ATTR3_LEAF_NULLOFF;
	}

	if (from->magic == XFS_ATTR3_LEAF_MAGIC) {
		hdr3 = (struct xfs_attr3_leaf_hdr *) to;
		hdr3->firstused = cpu_to_be16(firstused);
	} else {
		to->hdr.firstused = cpu_to_be16(firstused);
	}
}