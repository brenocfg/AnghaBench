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
struct btrfs_root {TYPE_1__* subv_writers; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 

void btrfs_end_write_no_snapshotting(struct btrfs_root *root)
{
	percpu_counter_dec(&root->subv_writers->counter);
	cond_wake_up(&root->subv_writers->wait);
}