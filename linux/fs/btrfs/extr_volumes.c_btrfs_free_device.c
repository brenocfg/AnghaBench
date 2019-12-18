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
struct btrfs_device {int /*<<< orphan*/  flush_bio; int /*<<< orphan*/  alloc_state; int /*<<< orphan*/  name; int /*<<< orphan*/  post_commit_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_io_tree_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_string_free (int /*<<< orphan*/ ) ; 

void btrfs_free_device(struct btrfs_device *device)
{
	WARN_ON(!list_empty(&device->post_commit_list));
	rcu_string_free(device->name);
	extent_io_tree_release(&device->alloc_state);
	bio_put(device->flush_bio);
	kfree(device);
}