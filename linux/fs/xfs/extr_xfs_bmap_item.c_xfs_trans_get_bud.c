#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct TYPE_4__ {int /*<<< orphan*/  bui_id; } ;
struct xfs_bui_log_item {TYPE_2__ bui_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  bud_bui_id; } ;
struct xfs_bud_log_item {int /*<<< orphan*/  bud_item; TYPE_1__ bud_format; struct xfs_bui_log_item* bud_buip; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_BUD ; 
 struct xfs_bud_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_bud_item_ops ; 
 int /*<<< orphan*/  xfs_bud_zone ; 
 int /*<<< orphan*/  xfs_log_item_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct xfs_bud_log_item *
xfs_trans_get_bud(
	struct xfs_trans		*tp,
	struct xfs_bui_log_item		*buip)
{
	struct xfs_bud_log_item		*budp;

	budp = kmem_zone_zalloc(xfs_bud_zone, 0);
	xfs_log_item_init(tp->t_mountp, &budp->bud_item, XFS_LI_BUD,
			  &xfs_bud_item_ops);
	budp->bud_buip = buip;
	budp->bud_format.bud_bui_id = buip->bui_format.bui_id;

	xfs_trans_add_item(tp, &budp->bud_item);
	return budp;
}