#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  li_ail; } ;
typedef  TYPE_1__ xfs_log_item_t ;
struct xfs_ail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_ail_check (struct xfs_ail*,TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_clear (struct xfs_ail*,TYPE_1__*) ; 

__attribute__((used)) static void
xfs_ail_delete(
	struct xfs_ail  *ailp,
	xfs_log_item_t  *lip)
{
	xfs_ail_check(ailp, lip);
	list_del(&lip->li_ail);
	xfs_trans_ail_cursor_clear(ailp, lip);
}