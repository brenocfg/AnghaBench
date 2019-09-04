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
struct xfs_rui_log_item {int dummy; } ;
struct xfs_rud_log_item {int /*<<< orphan*/  rud_item; } ;

/* Variables and functions */
 struct xfs_rud_log_item* xfs_rud_init (int /*<<< orphan*/ ,struct xfs_rui_log_item*) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ *) ; 

struct xfs_rud_log_item *
xfs_trans_get_rud(
	struct xfs_trans		*tp,
	struct xfs_rui_log_item		*ruip)
{
	struct xfs_rud_log_item		*rudp;

	rudp = xfs_rud_init(tp->t_mountp, ruip);
	xfs_trans_add_item(tp, &rudp->rud_item);
	return rudp;
}