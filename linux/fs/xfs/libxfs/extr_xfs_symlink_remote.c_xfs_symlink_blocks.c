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
struct TYPE_2__ {int /*<<< orphan*/  sb_blocksize; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 int XFS_SYMLINK_BUF_SPACE (struct xfs_mount*,int /*<<< orphan*/ ) ; 

int
xfs_symlink_blocks(
	struct xfs_mount *mp,
	int		pathlen)
{
	int buflen = XFS_SYMLINK_BUF_SPACE(mp, mp->m_sb.sb_blocksize);

	return (pathlen + buflen - 1) / buflen;
}