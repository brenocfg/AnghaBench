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
struct xfs_scrub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTNUM_CNT ; 
 int xchk_allocbt (struct xfs_scrub*,int /*<<< orphan*/ ) ; 

int
xchk_cntbt(
	struct xfs_scrub	*sc)
{
	return xchk_allocbt(sc, XFS_BTNUM_CNT);
}