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
struct TYPE_2__ {int /*<<< orphan*/  sb_agblocks; } ;
struct xfs_mount {TYPE_1__ m_sb; int /*<<< orphan*/  m_refc_mnr; int /*<<< orphan*/  m_refc_maxlevels; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_btree_compute_maxlevels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_refcountbt_compute_maxlevels(
	struct xfs_mount		*mp)
{
	mp->m_refc_maxlevels = xfs_btree_compute_maxlevels(
			mp->m_refc_mnr, mp->m_sb.sb_agblocks);
}