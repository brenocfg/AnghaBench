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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int sb_inopblock; scalar_t__ sb_agblocks; } ;
struct xfs_mount {scalar_t__* m_inobt_mxr; TYPE_1__ m_sb; int /*<<< orphan*/  m_inobt_mnr; } ;

/* Variables and functions */
 int XFS_INODES_PER_CHUNK ; 
 int /*<<< orphan*/  xfs_btree_calc_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static xfs_extlen_t
xfs_inobt_max_size(
	struct xfs_mount	*mp)
{
	/* Bail out if we're uninitialized, which can happen in mkfs. */
	if (mp->m_inobt_mxr[0] == 0)
		return 0;

	return xfs_btree_calc_size(mp->m_inobt_mnr,
		(uint64_t)mp->m_sb.sb_agblocks * mp->m_sb.sb_inopblock /
				XFS_INODES_PER_CHUNK);
}