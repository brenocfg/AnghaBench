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
struct xfs_buftarg {int /*<<< orphan*/  bt_lru; int /*<<< orphan*/  bt_io_count; int /*<<< orphan*/  bt_shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_buftarg*) ; 
 int /*<<< orphan*/  list_lru_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_blkdev_issue_flush (struct xfs_buftarg*) ; 

void
xfs_free_buftarg(
	struct xfs_buftarg	*btp)
{
	unregister_shrinker(&btp->bt_shrinker);
	ASSERT(percpu_counter_sum(&btp->bt_io_count) == 0);
	percpu_counter_destroy(&btp->bt_io_count);
	list_lru_destroy(&btp->bt_lru);

	xfs_blkdev_issue_flush(btp);

	kmem_free(btp);
}