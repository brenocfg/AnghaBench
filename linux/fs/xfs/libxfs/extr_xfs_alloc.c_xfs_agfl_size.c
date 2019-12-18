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
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct TYPE_2__ {unsigned int sb_sectsize; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_agfl {int dummy; } ;

/* Variables and functions */
 scalar_t__ xfs_sb_version_hascrc (TYPE_1__*) ; 

unsigned int
xfs_agfl_size(
	struct xfs_mount	*mp)
{
	unsigned int		size = mp->m_sb.sb_sectsize;

	if (xfs_sb_version_hascrc(&mp->m_sb))
		size -= sizeof(struct xfs_agfl);

	return size / sizeof(xfs_agblock_t);
}