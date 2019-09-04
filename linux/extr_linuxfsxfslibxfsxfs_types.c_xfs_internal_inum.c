#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_ino_t ;
struct TYPE_3__ {scalar_t__ sb_rbmino; scalar_t__ sb_rsumino; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 scalar_t__ xfs_is_quota_inode (TYPE_1__*,scalar_t__) ; 
 scalar_t__ xfs_sb_version_hasquota (TYPE_1__*) ; 

bool
xfs_internal_inum(
	struct xfs_mount	*mp,
	xfs_ino_t		ino)
{
	return ino == mp->m_sb.sb_rbmino || ino == mp->m_sb.sb_rsumino ||
		(xfs_sb_version_hasquota(&mp->m_sb) &&
		 xfs_is_quota_inode(&mp->m_sb, ino));
}