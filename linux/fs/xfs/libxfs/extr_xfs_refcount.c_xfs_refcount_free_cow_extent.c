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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct xfs_trans {struct xfs_mount* t_mountp; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_FSB_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_REFCOUNT_FREE_COW ; 
 int /*<<< orphan*/  XFS_RMAP_OWN_COW ; 
 int /*<<< orphan*/  __xfs_refcount_add (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_rmap_free_extent (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hasreflink (int /*<<< orphan*/ *) ; 

void
xfs_refcount_free_cow_extent(
	struct xfs_trans		*tp,
	xfs_fsblock_t			fsb,
	xfs_extlen_t			len)
{
	struct xfs_mount		*mp = tp->t_mountp;

	if (!xfs_sb_version_hasreflink(&mp->m_sb))
		return;

	/* Remove rmap entry */
	xfs_rmap_free_extent(tp, XFS_FSB_TO_AGNO(mp, fsb),
			XFS_FSB_TO_AGBNO(mp, fsb), len, XFS_RMAP_OWN_COW);
	__xfs_refcount_add(tp, XFS_REFCOUNT_FREE_COW, fsb, len);
}