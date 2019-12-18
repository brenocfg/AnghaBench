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
struct btrfs_root {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct btrfs_root*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void btrfs_put_fs_root(struct btrfs_root *root)
{
	if (refcount_dec_and_test(&root->refs))
		kfree(root);
}