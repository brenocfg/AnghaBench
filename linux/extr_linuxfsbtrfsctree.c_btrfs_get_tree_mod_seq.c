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
typedef  scalar_t__ u64 ;
struct seq_list {scalar_t__ seq; int /*<<< orphan*/  list; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_mod_log_lock; int /*<<< orphan*/  tree_mod_seq_lock; int /*<<< orphan*/  tree_mod_seq_list; } ;

/* Variables and functions */
 scalar_t__ btrfs_inc_tree_mod_seq (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

u64 btrfs_get_tree_mod_seq(struct btrfs_fs_info *fs_info,
			   struct seq_list *elem)
{
	write_lock(&fs_info->tree_mod_log_lock);
	spin_lock(&fs_info->tree_mod_seq_lock);
	if (!elem->seq) {
		elem->seq = btrfs_inc_tree_mod_seq(fs_info);
		list_add_tail(&elem->list, &fs_info->tree_mod_seq_list);
	}
	spin_unlock(&fs_info->tree_mod_seq_lock);
	write_unlock(&fs_info->tree_mod_log_lock);

	return elem->seq;
}