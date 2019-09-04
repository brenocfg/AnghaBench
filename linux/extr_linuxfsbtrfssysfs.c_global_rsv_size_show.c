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
struct kobject {int /*<<< orphan*/  parent; } ;
struct kobj_attribute {int dummy; } ;
struct btrfs_block_rsv {int /*<<< orphan*/  lock; int /*<<< orphan*/  size; } ;
struct btrfs_fs_info {struct btrfs_block_rsv global_block_rsv; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_show_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct btrfs_fs_info* to_fs_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t global_rsv_size_show(struct kobject *kobj,
				    struct kobj_attribute *ka, char *buf)
{
	struct btrfs_fs_info *fs_info = to_fs_info(kobj->parent);
	struct btrfs_block_rsv *block_rsv = &fs_info->global_block_rsv;
	return btrfs_show_u64(&block_rsv->size, &block_rsv->lock, buf);
}