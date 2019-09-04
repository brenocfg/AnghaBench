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
struct xfs_scrub {TYPE_1__* sm; } ;
struct xfs_btree_cur {int bc_flags; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sm_flags; } ;

/* Variables and functions */
 int XFS_BTREE_ROOT_IN_INODE ; 
 int /*<<< orphan*/  trace_xchk_btree_error (struct xfs_scrub*,struct xfs_btree_cur*,int,void*) ; 
 int /*<<< orphan*/  trace_xchk_ifork_btree_error (struct xfs_scrub*,struct xfs_btree_cur*,int,void*) ; 

__attribute__((used)) static void
__xchk_btree_set_corrupt(
	struct xfs_scrub	*sc,
	struct xfs_btree_cur	*cur,
	int			level,
	__u32			errflag,
	void			*ret_ip)
{
	sc->sm->sm_flags |= errflag;

	if (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE)
		trace_xchk_ifork_btree_error(sc, cur, level,
				ret_ip);
	else
		trace_xchk_btree_error(sc, cur, level,
				ret_ip);
}