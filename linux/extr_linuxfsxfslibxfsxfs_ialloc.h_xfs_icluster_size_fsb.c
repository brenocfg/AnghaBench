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
struct TYPE_2__ {int sb_blocksize; int sb_blocklog; } ;
struct xfs_mount {int m_inode_cluster_size; TYPE_1__ m_sb; } ;

/* Variables and functions */

__attribute__((used)) static inline int
xfs_icluster_size_fsb(
	struct xfs_mount	*mp)
{
	if (mp->m_sb.sb_blocksize >= mp->m_inode_cluster_size)
		return 1;
	return mp->m_inode_cluster_size >> mp->m_sb.sb_blocklog;
}