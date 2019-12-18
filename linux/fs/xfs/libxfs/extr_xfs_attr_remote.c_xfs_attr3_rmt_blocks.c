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
 int XFS_ATTR3_RMT_BUF_SPACE (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_B_TO_FSB (struct xfs_mount*,int) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 

int
xfs_attr3_rmt_blocks(
	struct xfs_mount *mp,
	int		attrlen)
{
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		int buflen = XFS_ATTR3_RMT_BUF_SPACE(mp, mp->m_sb.sb_blocksize);
		return (attrlen + buflen - 1) / buflen;
	}
	return XFS_B_TO_FSB(mp, attrlen);
}