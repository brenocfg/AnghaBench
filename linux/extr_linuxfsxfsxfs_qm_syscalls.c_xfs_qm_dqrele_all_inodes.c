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
typedef  int /*<<< orphan*/  uint ;
struct xfs_mount {int /*<<< orphan*/  m_quotainfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_AGITER_INEW_WAIT ; 
 int /*<<< orphan*/  xfs_dqrele_inode ; 
 int /*<<< orphan*/  xfs_inode_ag_iterator_flags (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
xfs_qm_dqrele_all_inodes(
	struct xfs_mount *mp,
	uint		 flags)
{
	ASSERT(mp->m_quotainfo);
	xfs_inode_ag_iterator_flags(mp, xfs_dqrele_inode, flags, NULL,
				    XFS_AGITER_INEW_WAIT);
}