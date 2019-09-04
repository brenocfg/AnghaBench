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
struct xfs_log_item {int /*<<< orphan*/  li_flags; struct xfs_ail* li_ailp; } ;
struct xfs_ail {int /*<<< orphan*/  ail_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_IN_AIL ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_ail_delete (struct xfs_ail*,struct xfs_log_item*,int) ; 

__attribute__((used)) static inline void
xfs_trans_ail_remove(
	struct xfs_log_item	*lip,
	int			shutdown_type)
{
	struct xfs_ail		*ailp = lip->li_ailp;

	spin_lock(&ailp->ail_lock);
	/* xfs_trans_ail_delete() drops the AIL lock */
	if (test_bit(XFS_LI_IN_AIL, &lip->li_flags))
		xfs_trans_ail_delete(ailp, lip, shutdown_type);
	else
		spin_unlock(&ailp->ail_lock);
}