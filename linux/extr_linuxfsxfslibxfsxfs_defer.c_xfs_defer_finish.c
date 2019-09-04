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
struct xfs_trans {int t_flags; int /*<<< orphan*/  t_mountp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 int XFS_TRANS_DIRTY ; 
 int xfs_defer_finish_noroll (struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_defer_reset (struct xfs_trans*) ; 
 int xfs_defer_trans_roll (struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_force_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_defer_finish(
	struct xfs_trans	**tp)
{
	int			error;

	/*
	 * Finish and roll the transaction once more to avoid returning to the
	 * caller with a dirty transaction.
	 */
	error = xfs_defer_finish_noroll(tp);
	if (error)
		return error;
	if ((*tp)->t_flags & XFS_TRANS_DIRTY) {
		error = xfs_defer_trans_roll(tp);
		if (error) {
			xfs_force_shutdown((*tp)->t_mountp,
					   SHUTDOWN_CORRUPT_INCORE);
			return error;
		}
	}
	xfs_defer_reset(*tp);
	return 0;
}