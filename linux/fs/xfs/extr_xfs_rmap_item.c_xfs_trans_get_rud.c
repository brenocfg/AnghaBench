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
struct TYPE_4__ {int /*<<< orphan*/  rui_id; } ;
struct xfs_rui_log_item {TYPE_2__ rui_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  rud_rui_id; } ;
struct xfs_rud_log_item {int /*<<< orphan*/  rud_item; TYPE_1__ rud_format; struct xfs_rui_log_item* rud_ruip; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_RUD ; 
 struct xfs_rud_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_item_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_rud_item_ops ; 
 int /*<<< orphan*/  xfs_rud_zone ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct xfs_rud_log_item *
xfs_trans_get_rud(
	struct xfs_trans		*tp,
	struct xfs_rui_log_item		*ruip)
{
	struct xfs_rud_log_item		*rudp;

	rudp = kmem_zone_zalloc(xfs_rud_zone, 0);
	xfs_log_item_init(tp->t_mountp, &rudp->rud_item, XFS_LI_RUD,
			  &xfs_rud_item_ops);
	rudp->rud_ruip = ruip;
	rudp->rud_format.rud_rui_id = ruip->rui_format.rui_id;

	xfs_trans_add_item(tp, &rudp->rud_item);
	return rudp;
}