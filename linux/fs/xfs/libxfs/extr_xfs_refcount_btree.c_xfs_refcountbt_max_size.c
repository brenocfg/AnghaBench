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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct xfs_mount {scalar_t__* m_refc_mxr; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_refcountbt_calc_size (struct xfs_mount*,int /*<<< orphan*/ ) ; 

xfs_extlen_t
xfs_refcountbt_max_size(
	struct xfs_mount	*mp,
	xfs_agblock_t		agblocks)
{
	/* Bail out if we're uninitialized, which can happen in mkfs. */
	if (mp->m_refc_mxr[0] == 0)
		return 0;

	return xfs_refcountbt_calc_size(mp, agblocks);
}