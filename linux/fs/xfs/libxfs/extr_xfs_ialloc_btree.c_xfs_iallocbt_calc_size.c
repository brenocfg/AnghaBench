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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inobt_mnr; } ;

/* Variables and functions */
 TYPE_1__* M_IGEO (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_btree_calc_size (int /*<<< orphan*/ ,unsigned long long) ; 

xfs_extlen_t
xfs_iallocbt_calc_size(
	struct xfs_mount	*mp,
	unsigned long long	len)
{
	return xfs_btree_calc_size(M_IGEO(mp)->inobt_mnr, len);
}