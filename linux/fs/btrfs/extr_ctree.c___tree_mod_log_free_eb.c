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
struct tree_mod_elem {int /*<<< orphan*/  node; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_mod_log; } ;

/* Variables and functions */
 int __tree_mod_log_insert (struct btrfs_fs_info*,struct tree_mod_elem*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
__tree_mod_log_free_eb(struct btrfs_fs_info *fs_info,
		       struct tree_mod_elem **tm_list,
		       int nritems)
{
	int i, j;
	int ret;

	for (i = nritems - 1; i >= 0; i--) {
		ret = __tree_mod_log_insert(fs_info, tm_list[i]);
		if (ret) {
			for (j = nritems - 1; j > i; j--)
				rb_erase(&tm_list[j]->node,
					 &fs_info->tree_mod_log);
			return ret;
		}
	}

	return 0;
}