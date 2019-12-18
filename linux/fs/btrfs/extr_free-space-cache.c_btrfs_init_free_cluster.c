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
struct btrfs_free_cluster {int fragmented; int /*<<< orphan*/ * block_group; int /*<<< orphan*/  block_group_list; scalar_t__ max_size; int /*<<< orphan*/  root; int /*<<< orphan*/  refill_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void btrfs_init_free_cluster(struct btrfs_free_cluster *cluster)
{
	spin_lock_init(&cluster->lock);
	spin_lock_init(&cluster->refill_lock);
	cluster->root = RB_ROOT;
	cluster->max_size = 0;
	cluster->fragmented = false;
	INIT_LIST_HEAD(&cluster->block_group_list);
	cluster->block_group = NULL;
}