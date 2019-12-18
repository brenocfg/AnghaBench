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
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; } ;
struct btrfs_delayed_ref_head {int /*<<< orphan*/  mutex; int /*<<< orphan*/  href_node; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_put_delayed_ref_head (struct btrfs_delayed_ref_head*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_delayed_ref_lock(struct btrfs_delayed_ref_root *delayed_refs,
			   struct btrfs_delayed_ref_head *head)
{
	lockdep_assert_held(&delayed_refs->lock);
	if (mutex_trylock(&head->mutex))
		return 0;

	refcount_inc(&head->refs);
	spin_unlock(&delayed_refs->lock);

	mutex_lock(&head->mutex);
	spin_lock(&delayed_refs->lock);
	if (RB_EMPTY_NODE(&head->href_node)) {
		mutex_unlock(&head->mutex);
		btrfs_put_delayed_ref_head(head);
		return -EAGAIN;
	}
	btrfs_put_delayed_ref_head(head);
	return 0;
}