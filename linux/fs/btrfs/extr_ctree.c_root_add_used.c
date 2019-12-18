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
typedef  scalar_t__ u32 ;
struct btrfs_root {int /*<<< orphan*/  accounting_lock; int /*<<< orphan*/  root_item; } ;

/* Variables and functions */
 scalar_t__ btrfs_root_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_set_root_used (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void root_add_used(struct btrfs_root *root, u32 size)
{
	spin_lock(&root->accounting_lock);
	btrfs_set_root_used(&root->root_item,
			    btrfs_root_used(&root->root_item) + size);
	spin_unlock(&root->accounting_lock);
}