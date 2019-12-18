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
struct xfs_bui_log_item {int /*<<< orphan*/  bui_item; int /*<<< orphan*/  bui_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SHUTDOWN_LOG_IO_ERROR ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_bui_item_free (struct xfs_bui_log_item*) ; 
 int /*<<< orphan*/  xfs_trans_ail_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
xfs_bui_release(
	struct xfs_bui_log_item	*buip)
{
	ASSERT(atomic_read(&buip->bui_refcount) > 0);
	if (atomic_dec_and_test(&buip->bui_refcount)) {
		xfs_trans_ail_remove(&buip->bui_item, SHUTDOWN_LOG_IO_ERROR);
		xfs_bui_item_free(buip);
	}
}