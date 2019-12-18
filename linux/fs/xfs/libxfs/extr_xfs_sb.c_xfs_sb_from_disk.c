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
typedef  int /*<<< orphan*/  xfs_dsb_t ;
struct xfs_sb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xfs_sb_from_disk (struct xfs_sb*,int /*<<< orphan*/ *,int) ; 

void
xfs_sb_from_disk(
	struct xfs_sb	*to,
	xfs_dsb_t	*from)
{
	__xfs_sb_from_disk(to, from, true);
}