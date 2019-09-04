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
typedef  int /*<<< orphan*/  uint ;
struct xfs_scrub {int dummy; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int xchk_trans_alloc (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xrep_calc_ag_resblks (struct xfs_scrub*) ; 

int
xchk_setup_fs(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	uint			resblks;

	resblks = xrep_calc_ag_resblks(sc);
	return xchk_trans_alloc(sc, resblks);
}