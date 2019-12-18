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
struct xfs_inode {int dummy; } ;
struct xfs_ifork {int dummy; } ;
struct xfs_iext_cursor {scalar_t__ pos; int /*<<< orphan*/  leaf; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  cur_rec (struct xfs_iext_cursor*) ; 
 int /*<<< orphan*/  trace_xfs_bmap_post_update (struct xfs_inode*,struct xfs_iext_cursor*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_bmap_pre_update (struct xfs_inode*,struct xfs_iext_cursor*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_get (struct xfs_bmbt_irec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_inc_seq (struct xfs_ifork*) ; 
 int /*<<< orphan*/  xfs_iext_set (int /*<<< orphan*/ ,struct xfs_bmbt_irec*) ; 
 struct xfs_ifork* xfs_iext_state_to_fork (struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_iext_update_node (struct xfs_ifork*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 

void
xfs_iext_update_extent(
	struct xfs_inode	*ip,
	int			state,
	struct xfs_iext_cursor	*cur,
	struct xfs_bmbt_irec	*new)
{
	struct xfs_ifork	*ifp = xfs_iext_state_to_fork(ip, state);

	xfs_iext_inc_seq(ifp);

	if (cur->pos == 0) {
		struct xfs_bmbt_irec	old;

		xfs_iext_get(&old, cur_rec(cur));
		if (new->br_startoff != old.br_startoff) {
			xfs_iext_update_node(ifp, old.br_startoff,
					new->br_startoff, 1, cur->leaf);
		}
	}

	trace_xfs_bmap_pre_update(ip, cur, state, _RET_IP_);
	xfs_iext_set(cur_rec(cur), new);
	trace_xfs_bmap_post_update(ip, cur, state, _RET_IP_);
}