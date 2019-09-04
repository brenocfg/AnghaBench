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
struct xfs_trans {int t_flags; int /*<<< orphan*/  t_dfops; } ;

/* Variables and functions */
 int XFS_TRANS_LOWMODE ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_defer_reset (struct xfs_trans*) ; 

void
xfs_defer_move(
	struct xfs_trans	*dtp,
	struct xfs_trans	*stp)
{
	list_splice_init(&stp->t_dfops, &dtp->t_dfops);

	/*
	 * Low free space mode was historically controlled by a dfops field.
	 * This meant that low mode state potentially carried across multiple
	 * transaction rolls. Transfer low mode on a dfops move to preserve
	 * that behavior.
	 */
	dtp->t_flags |= (stp->t_flags & XFS_TRANS_LOWMODE);

	xfs_defer_reset(stp);
}