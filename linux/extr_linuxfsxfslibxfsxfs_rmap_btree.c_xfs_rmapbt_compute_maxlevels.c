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
struct TYPE_2__ {int /*<<< orphan*/  sb_agblocks; } ;
struct xfs_mount {TYPE_1__ m_sb; int /*<<< orphan*/  m_rmap_mnr; int /*<<< orphan*/  m_rmap_maxlevels; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTREE_MAXLEVELS ; 
 int /*<<< orphan*/  xfs_btree_compute_maxlevels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hasreflink (TYPE_1__*) ; 

void
xfs_rmapbt_compute_maxlevels(
	struct xfs_mount		*mp)
{
	/*
	 * On a non-reflink filesystem, the maximum number of rmap
	 * records is the number of blocks in the AG, hence the max
	 * rmapbt height is log_$maxrecs($agblocks).  However, with
	 * reflink each AG block can have up to 2^32 (per the refcount
	 * record format) owners, which means that theoretically we
	 * could face up to 2^64 rmap records.
	 *
	 * That effectively means that the max rmapbt height must be
	 * XFS_BTREE_MAXLEVELS.  "Fortunately" we'll run out of AG
	 * blocks to feed the rmapbt long before the rmapbt reaches
	 * maximum height.  The reflink code uses ag_resv_critical to
	 * disallow reflinking when less than 10% of the per-AG metadata
	 * block reservation since the fallback is a regular file copy.
	 */
	if (xfs_sb_version_hasreflink(&mp->m_sb))
		mp->m_rmap_maxlevels = XFS_BTREE_MAXLEVELS;
	else
		mp->m_rmap_maxlevels = xfs_btree_compute_maxlevels(
				mp->m_rmap_mnr, mp->m_sb.sb_agblocks);
}