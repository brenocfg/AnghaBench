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
struct xfs_log_item {int /*<<< orphan*/  li_ail; } ;
struct xfs_ail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_ail_check (struct xfs_ail*,struct xfs_log_item*) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_clear (struct xfs_ail*,struct xfs_log_item*) ; 

__attribute__((used)) static void
xfs_ail_delete(
	struct xfs_ail		*ailp,
	struct xfs_log_item	*lip)
{
	xfs_ail_check(ailp, lip);
	list_del(&lip->li_ail);
	xfs_trans_ail_cursor_clear(ailp, lip);
}