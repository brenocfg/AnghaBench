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
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {scalar_t__ send_in_progress; int /*<<< orphan*/  root_item_lock; TYPE_1__ root_key; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_root_dec_send_in_progress(struct btrfs_root* root)
{
	spin_lock(&root->root_item_lock);
	root->send_in_progress--;
	/*
	 * Not much left to do, we don't know why it's unbalanced and
	 * can't blindly reset it to 0.
	 */
	if (root->send_in_progress < 0)
		btrfs_err(root->fs_info,
			  "send_in_progress unbalanced %d root %llu",
			  root->send_in_progress, root->root_key.objectid);
	spin_unlock(&root->root_item_lock);
}