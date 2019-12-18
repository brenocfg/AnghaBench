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
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRAMFS_BLOCKDEV ; 
 int /*<<< orphan*/  CONFIG_CRAMFS_MTD ; 
 int ENOPROTOOPT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cramfs_blkdev_fill_super ; 
 int /*<<< orphan*/  cramfs_mtd_fill_super ; 
 int get_tree_bdev (struct fs_context*,int /*<<< orphan*/ ) ; 
 int get_tree_mtd (struct fs_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cramfs_get_tree(struct fs_context *fc)
{
	int ret = -ENOPROTOOPT;

	if (IS_ENABLED(CONFIG_CRAMFS_MTD)) {
		ret = get_tree_mtd(fc, cramfs_mtd_fill_super);
		if (ret < 0)
			return ret;
	}
	if (IS_ENABLED(CONFIG_CRAMFS_BLOCKDEV))
		ret = get_tree_bdev(fc, cramfs_blkdev_fill_super);
	return ret;
}