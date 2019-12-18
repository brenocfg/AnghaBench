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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct xfs_log_item {int /*<<< orphan*/  li_lsn; } ;
struct xfs_ail {int /*<<< orphan*/  ail_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct xfs_log_item* xfs_ail_max (struct xfs_ail*) ; 

__attribute__((used)) static xfs_lsn_t
xfs_ail_max_lsn(
	struct xfs_ail		*ailp)
{
	xfs_lsn_t       	lsn = 0;
	struct xfs_log_item	*lip;

	spin_lock(&ailp->ail_lock);
	lip = xfs_ail_max(ailp);
	if (lip)
		lsn = lip->li_lsn;
	spin_unlock(&ailp->ail_lock);

	return lsn;
}