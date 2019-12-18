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
struct xfs_scrub {int flags; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int XCHK_TRY_HARDER ; 
 int xchk_setup_ag_btree (struct xfs_scrub*,struct xfs_inode*,int) ; 

int
xchk_setup_ag_iallocbt(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	return xchk_setup_ag_btree(sc, ip, sc->flags & XCHK_TRY_HARDER);
}