#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  t_mountp; } ;
typedef  TYPE_1__ xfs_trans_t ;
struct TYPE_10__ {int /*<<< orphan*/  qql_item; } ;
typedef  TYPE_2__ xfs_qoff_logitem_t ;
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_2__* xfs_qm_qoff_logitem_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_add_item (TYPE_1__*,int /*<<< orphan*/ *) ; 

xfs_qoff_logitem_t *
xfs_trans_get_qoff_item(
	xfs_trans_t		*tp,
	xfs_qoff_logitem_t	*startqoff,
	uint			flags)
{
	xfs_qoff_logitem_t	*q;

	ASSERT(tp != NULL);

	q = xfs_qm_qoff_logitem_init(tp->t_mountp, startqoff, flags);
	ASSERT(q != NULL);

	/*
	 * Get a log_item_desc to point at the new item.
	 */
	xfs_trans_add_item(tp, &q->qql_item);
	return q;
}