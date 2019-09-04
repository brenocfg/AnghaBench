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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__ sb_blocksize; int sb_agblocks; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 scalar_t__ MAXEXTLEN ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int XFS_DIFLAG2_COWEXTSIZE ; 
 int XFS_DIFLAG_REALTIME ; 
 scalar_t__ XFS_FSB_TO_B (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/ * __this_address ; 
 int /*<<< orphan*/  xfs_sb_version_hasreflink (TYPE_1__*) ; 

xfs_failaddr_t
xfs_inode_validate_cowextsize(
	struct xfs_mount		*mp,
	uint32_t			cowextsize,
	uint16_t			mode,
	uint16_t			flags,
	uint64_t			flags2)
{
	bool				rt_flag;
	bool				hint_flag;
	uint32_t			cowextsize_bytes;

	rt_flag = (flags & XFS_DIFLAG_REALTIME);
	hint_flag = (flags2 & XFS_DIFLAG2_COWEXTSIZE);
	cowextsize_bytes = XFS_FSB_TO_B(mp, cowextsize);

	if (hint_flag && !xfs_sb_version_hasreflink(&mp->m_sb))
		return __this_address;

	if (hint_flag && !(S_ISDIR(mode) || S_ISREG(mode)))
		return __this_address;

	if (hint_flag && cowextsize == 0)
		return __this_address;

	/* free inodes get flags set to zero but cowextsize remains */
	if (mode && !hint_flag && cowextsize != 0)
		return __this_address;

	if (hint_flag && rt_flag)
		return __this_address;

	if (cowextsize_bytes % mp->m_sb.sb_blocksize)
		return __this_address;

	if (cowextsize > MAXEXTLEN)
		return __this_address;

	if (cowextsize > mp->m_sb.sb_agblocks / 2)
		return __this_address;

	return NULL;
}