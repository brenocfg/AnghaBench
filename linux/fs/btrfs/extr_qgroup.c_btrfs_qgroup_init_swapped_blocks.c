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
struct btrfs_qgroup_swapped_blocks {int swapped; int /*<<< orphan*/ * blocks; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BTRFS_MAX_LEVEL ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void btrfs_qgroup_init_swapped_blocks(
	struct btrfs_qgroup_swapped_blocks *swapped_blocks)
{
	int i;

	spin_lock_init(&swapped_blocks->lock);
	for (i = 0; i < BTRFS_MAX_LEVEL; i++)
		swapped_blocks->blocks[i] = RB_ROOT;
	swapped_blocks->swapped = false;
}