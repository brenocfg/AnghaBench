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
struct TYPE_4__ {int /*<<< orphan*/  cui_id; } ;
struct xfs_cui_log_item {TYPE_2__ cui_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  cud_cui_id; } ;
struct xfs_cud_log_item {int /*<<< orphan*/  cud_item; TYPE_1__ cud_format; struct xfs_cui_log_item* cud_cuip; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_CUD ; 
 struct xfs_cud_log_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_cud_item_ops ; 
 int /*<<< orphan*/  xfs_cud_zone ; 
 int /*<<< orphan*/  xfs_log_item_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct xfs_cud_log_item *
xfs_trans_get_cud(
	struct xfs_trans		*tp,
	struct xfs_cui_log_item		*cuip)
{
	struct xfs_cud_log_item		*cudp;

	cudp = kmem_zone_zalloc(xfs_cud_zone, 0);
	xfs_log_item_init(tp->t_mountp, &cudp->cud_item, XFS_LI_CUD,
			  &xfs_cud_item_ops);
	cudp->cud_cuip = cuip;
	cudp->cud_format.cud_cui_id = cuip->cui_format.cui_id;

	xfs_trans_add_item(tp, &cudp->cud_item);
	return cudp;
}