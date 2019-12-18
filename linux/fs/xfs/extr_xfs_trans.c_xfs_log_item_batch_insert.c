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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct xfs_log_item {TYPE_1__* li_ops; } ;
struct xfs_ail_cursor {int dummy; } ;
struct xfs_ail {int /*<<< orphan*/  ail_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iop_unpin ) (struct xfs_log_item*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xfs_log_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ail_update_bulk (struct xfs_ail*,struct xfs_ail_cursor*,struct xfs_log_item**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
xfs_log_item_batch_insert(
	struct xfs_ail		*ailp,
	struct xfs_ail_cursor	*cur,
	struct xfs_log_item	**log_items,
	int			nr_items,
	xfs_lsn_t		commit_lsn)
{
	int	i;

	spin_lock(&ailp->ail_lock);
	/* xfs_trans_ail_update_bulk drops ailp->ail_lock */
	xfs_trans_ail_update_bulk(ailp, cur, log_items, nr_items, commit_lsn);

	for (i = 0; i < nr_items; i++) {
		struct xfs_log_item *lip = log_items[i];

		if (lip->li_ops->iop_unpin)
			lip->li_ops->iop_unpin(lip, 0);
	}
}