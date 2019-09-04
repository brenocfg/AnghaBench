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
struct btrfs_free_space_ctl {int /*<<< orphan*/  tree_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btrfs_remove_free_space_cache_locked (struct btrfs_free_space_ctl*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __btrfs_remove_free_space_cache(struct btrfs_free_space_ctl *ctl)
{
	spin_lock(&ctl->tree_lock);
	__btrfs_remove_free_space_cache_locked(ctl);
	spin_unlock(&ctl->tree_lock);
}