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
struct reada_extent {int /*<<< orphan*/  refcnt; } ;
struct extent_buffer {int start; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  reada_lock; int /*<<< orphan*/  reada_tree; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __readahead_hook (struct btrfs_fs_info*,struct reada_extent*,struct extent_buffer*,int) ; 
 struct reada_extent* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reada_extent_put (struct btrfs_fs_info*,struct reada_extent*) ; 
 int /*<<< orphan*/  reada_start_machine (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btree_readahead_hook(struct extent_buffer *eb, int err)
{
	struct btrfs_fs_info *fs_info = eb->fs_info;
	int ret = 0;
	struct reada_extent *re;

	/* find extent */
	spin_lock(&fs_info->reada_lock);
	re = radix_tree_lookup(&fs_info->reada_tree,
			       eb->start >> PAGE_SHIFT);
	if (re)
		re->refcnt++;
	spin_unlock(&fs_info->reada_lock);
	if (!re) {
		ret = -1;
		goto start_machine;
	}

	__readahead_hook(fs_info, re, eb, err);
	reada_extent_put(fs_info, re);	/* our ref */

start_machine:
	reada_start_machine(fs_info);
	return ret;
}