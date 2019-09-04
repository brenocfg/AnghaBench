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
struct TYPE_2__ {scalar_t__ sb_inoalignmt; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 scalar_t__ xfs_icluster_size_fsb (struct xfs_mount*) ; 
 scalar_t__ xfs_sb_version_hasalign (TYPE_1__*) ; 

int
xfs_ialloc_cluster_alignment(
	struct xfs_mount	*mp)
{
	if (xfs_sb_version_hasalign(&mp->m_sb) &&
	    mp->m_sb.sb_inoalignmt >= xfs_icluster_size_fsb(mp))
		return mp->m_sb.sb_inoalignmt;
	return 1;
}