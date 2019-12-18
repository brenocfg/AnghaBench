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
struct btrfs_full_stripe_locks_tree {int /*<<< orphan*/  lock; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void btrfs_init_full_stripe_locks_tree(
			struct btrfs_full_stripe_locks_tree *locks_root)
{
	locks_root->root = RB_ROOT;
	mutex_init(&locks_root->lock);
}