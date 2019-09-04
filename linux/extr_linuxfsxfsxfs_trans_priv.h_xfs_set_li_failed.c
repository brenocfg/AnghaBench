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
struct xfs_log_item {struct xfs_buf* li_buf; int /*<<< orphan*/  li_flags; TYPE_1__* li_ailp; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ail_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_FAILED ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_hold (struct xfs_buf*) ; 

__attribute__((used)) static inline void
xfs_set_li_failed(
	struct xfs_log_item	*lip,
	struct xfs_buf		*bp)
{
	lockdep_assert_held(&lip->li_ailp->ail_lock);

	if (!test_and_set_bit(XFS_LI_FAILED, &lip->li_flags)) {
		xfs_buf_hold(bp);
		lip->li_buf = bp;
	}
}