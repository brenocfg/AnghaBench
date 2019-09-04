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
struct xfs_log_item {int dummy; } ;
struct xfs_ail_cursor {struct xfs_log_item* item; } ;
struct xfs_ail {int dummy; } ;

/* Variables and functions */
 struct xfs_log_item* __xfs_trans_ail_cursor_last (struct xfs_ail*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_init (struct xfs_ail*,struct xfs_ail_cursor*) ; 

struct xfs_log_item *
xfs_trans_ail_cursor_last(
	struct xfs_ail		*ailp,
	struct xfs_ail_cursor	*cur,
	xfs_lsn_t		lsn)
{
	xfs_trans_ail_cursor_init(ailp, cur);
	cur->item = __xfs_trans_ail_cursor_last(ailp, lsn);
	return cur->item;
}