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
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 

bool
xfs_dinode_good_version(
	struct xfs_mount *mp,
	__u8		version)
{
	if (xfs_sb_version_hascrc(&mp->m_sb))
		return version == 3;

	return version == 1 || version == 2;
}