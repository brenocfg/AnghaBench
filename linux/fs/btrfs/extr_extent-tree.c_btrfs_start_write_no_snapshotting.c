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
struct btrfs_root {int /*<<< orphan*/  will_be_snapshotted; TYPE_1__* subv_writers; } ;
struct TYPE_2__ {int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_end_write_no_snapshotting (struct btrfs_root*) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 

int btrfs_start_write_no_snapshotting(struct btrfs_root *root)
{
	if (atomic_read(&root->will_be_snapshotted))
		return 0;

	percpu_counter_inc(&root->subv_writers->counter);
	/*
	 * Make sure counter is updated before we check for snapshot creation.
	 */
	smp_mb();
	if (atomic_read(&root->will_be_snapshotted)) {
		btrfs_end_write_no_snapshotting(root);
		return 0;
	}
	return 1;
}