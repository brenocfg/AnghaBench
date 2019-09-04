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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  sb_inodesize; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_dinode {int di_version; int /*<<< orphan*/  di_crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DINODE_CRC_OFF ; 
 int /*<<< orphan*/  xfs_end_cksum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_start_cksum_update (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_dinode_calc_crc(
	struct xfs_mount	*mp,
	struct xfs_dinode	*dip)
{
	uint32_t		crc;

	if (dip->di_version < 3)
		return;

	ASSERT(xfs_sb_version_hascrc(&mp->m_sb));
	crc = xfs_start_cksum_update((char *)dip, mp->m_sb.sb_inodesize,
			      XFS_DINODE_CRC_OFF);
	dip->di_crc = xfs_end_cksum(crc);
}