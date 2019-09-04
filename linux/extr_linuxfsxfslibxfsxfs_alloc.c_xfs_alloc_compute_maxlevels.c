#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sb_agblocks; } ;
struct TYPE_5__ {TYPE_1__ m_sb; int /*<<< orphan*/  m_alloc_mnr; int /*<<< orphan*/  m_ag_maxlevels; } ;
typedef  TYPE_2__ xfs_mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_btree_compute_maxlevels (int /*<<< orphan*/ ,int) ; 

void
xfs_alloc_compute_maxlevels(
	xfs_mount_t	*mp)	/* file system mount structure */
{
	mp->m_ag_maxlevels = xfs_btree_compute_maxlevels(mp->m_alloc_mnr,
			(mp->m_sb.sb_agblocks + 1) / 2);
}