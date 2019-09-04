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
struct xfs_cui_log_item {int dummy; } ;
struct xfs_cud_log_item {int /*<<< orphan*/  cud_item; } ;

/* Variables and functions */
 struct xfs_cud_log_item* xfs_cud_init (int /*<<< orphan*/ ,struct xfs_cui_log_item*) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

struct xfs_cud_log_item *
xfs_trans_get_cud(
	struct xfs_trans		*tp,
	struct xfs_cui_log_item		*cuip)
{
	struct xfs_cud_log_item		*cudp;

	cudp = xfs_cud_init(tp->t_mountp, cuip);
	xfs_trans_add_item(tp, &cudp->cud_item);
	return cudp;
}