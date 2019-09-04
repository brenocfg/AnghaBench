#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_trans {int /*<<< orphan*/  t_items; TYPE_1__* t_mountp; } ;
struct xfs_log_item {scalar_t__ li_ailp; int /*<<< orphan*/  li_trans; int /*<<< orphan*/  li_flags; TYPE_1__* li_mountp; } ;
struct TYPE_2__ {scalar_t__ m_ail; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_trans_add_item (struct xfs_trans*,int /*<<< orphan*/ ) ; 

void
xfs_trans_add_item(
	struct xfs_trans	*tp,
	struct xfs_log_item	*lip)
{
	ASSERT(lip->li_mountp == tp->t_mountp);
	ASSERT(lip->li_ailp == tp->t_mountp->m_ail);
	ASSERT(list_empty(&lip->li_trans));
	ASSERT(!test_bit(XFS_LI_DIRTY, &lip->li_flags));

	list_add_tail(&lip->li_trans, &tp->t_items);
	trace_xfs_trans_add_item(tp, _RET_IP_);
}