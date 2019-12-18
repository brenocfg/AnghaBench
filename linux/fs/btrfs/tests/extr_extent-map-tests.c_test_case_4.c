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
struct extent_map_tree {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_4K ; 
 int __test_case_4 (struct btrfs_fs_info*,struct extent_map_tree*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_case_4(struct btrfs_fs_info *fs_info,
		struct extent_map_tree *em_tree)
{
	int ret;

	ret = __test_case_4(fs_info, em_tree, 0);
	if (ret)
		return ret;
	ret = __test_case_4(fs_info, em_tree, SZ_4K);

	return ret;
}