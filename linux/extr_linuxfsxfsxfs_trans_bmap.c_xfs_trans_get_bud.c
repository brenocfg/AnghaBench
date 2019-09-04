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
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_bui_log_item {int dummy; } ;
struct xfs_bud_log_item {int /*<<< orphan*/  bud_item; } ;

/* Variables and functions */
 struct xfs_bud_log_item* xfs_bud_init (int /*<<< orphan*/ ,struct xfs_bui_log_item*) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

struct xfs_bud_log_item *
xfs_trans_get_bud(
	struct xfs_trans		*tp,
	struct xfs_bui_log_item		*buip)
{
	struct xfs_bud_log_item		*budp;

	budp = xfs_bud_init(tp->t_mountp, buip);
	xfs_trans_add_item(tp, &budp->bud_item);
	return budp;
}