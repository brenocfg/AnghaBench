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
typedef  int /*<<< orphan*/  uint ;
struct xfs_log_item {TYPE_1__* li_ops; } ;
struct xfs_ail {int /*<<< orphan*/  ail_buf_list; int /*<<< orphan*/  ail_mount; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iop_push ) (struct xfs_log_item*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ERRTAG_LOG_ITEM_PIN ; 
 int /*<<< orphan*/  XFS_ITEM_PINNED ; 
 scalar_t__ XFS_TEST_ERROR (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_log_item*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint
xfsaild_push_item(
	struct xfs_ail		*ailp,
	struct xfs_log_item	*lip)
{
	/*
	 * If log item pinning is enabled, skip the push and track the item as
	 * pinned. This can help induce head-behind-tail conditions.
	 */
	if (XFS_TEST_ERROR(false, ailp->ail_mount, XFS_ERRTAG_LOG_ITEM_PIN))
		return XFS_ITEM_PINNED;

	/*
	 * Consider the item pinned if a push callback is not defined so the
	 * caller will force the log. This should only happen for intent items
	 * as they are unpinned once the associated done item is committed to
	 * the on-disk log.
	 */
	if (!lip->li_ops->iop_push)
		return XFS_ITEM_PINNED;
	return lip->li_ops->iop_push(lip, &ailp->ail_buf_list);
}