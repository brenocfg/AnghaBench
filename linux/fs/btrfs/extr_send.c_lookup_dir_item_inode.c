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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ type; int /*<<< orphan*/  objectid; } ;
struct btrfs_dir_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_ROOT_ITEM_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR_OR_NULL (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 struct btrfs_path* alloc_path_for_send () ; 
 int /*<<< orphan*/  btrfs_dir_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_dir_item*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_dir_type (int /*<<< orphan*/ ,struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 struct btrfs_dir_item* btrfs_lookup_dir_item (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lookup_dir_item_inode(struct btrfs_root *root,
				 u64 dir, const char *name, int name_len,
				 u64 *found_inode,
				 u8 *found_type)
{
	int ret = 0;
	struct btrfs_dir_item *di;
	struct btrfs_key key;
	struct btrfs_path *path;

	path = alloc_path_for_send();
	if (!path)
		return -ENOMEM;

	di = btrfs_lookup_dir_item(NULL, root, path,
			dir, name, name_len, 0);
	if (IS_ERR_OR_NULL(di)) {
		ret = di ? PTR_ERR(di) : -ENOENT;
		goto out;
	}
	btrfs_dir_item_key_to_cpu(path->nodes[0], di, &key);
	if (key.type == BTRFS_ROOT_ITEM_KEY) {
		ret = -ENOENT;
		goto out;
	}
	*found_inode = key.objectid;
	*found_type = btrfs_dir_type(path->nodes[0], di);

out:
	btrfs_free_path(path);
	return ret;
}