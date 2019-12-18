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
struct btrfs_root {scalar_t__ node; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_IN_RADIX ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct btrfs_root*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_free_dummy_root(struct btrfs_root *root)
{
	if (!root)
		return;
	/* Will be freed by btrfs_free_fs_roots */
	if (WARN_ON(test_bit(BTRFS_ROOT_IN_RADIX, &root->state)))
		return;
	if (root->node) {
		/* One for allocate_extent_buffer */
		free_extent_buffer(root->node);
	}
	kfree(root);
}