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
typedef  int /*<<< orphan*/  u64 ;
struct inode {scalar_t__ i_nlink; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {int /*<<< orphan*/  objectid; } ;
struct btrfs_dir_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 int btrfs_add_link (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_dir_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_dir_item*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_ino (int /*<<< orphan*/ ) ; 
 struct btrfs_dir_item* btrfs_lookup_dir_item (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_run_delayed_items (struct btrfs_trans_handle*) ; 
 int btrfs_unlink_inode (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* read_one_inode (struct btrfs_root*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_link(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		    struct inode *dir, struct inode *inode, const char *name,
		    int namelen, u64 ref_index)
{
	struct btrfs_dir_item *dir_item;
	struct btrfs_key key;
	struct btrfs_path *path;
	struct inode *other_inode = NULL;
	int ret;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	dir_item = btrfs_lookup_dir_item(NULL, root, path,
					 btrfs_ino(BTRFS_I(dir)),
					 name, namelen, 0);
	if (!dir_item) {
		btrfs_release_path(path);
		goto add_link;
	} else if (IS_ERR(dir_item)) {
		ret = PTR_ERR(dir_item);
		goto out;
	}

	/*
	 * Our inode's dentry collides with the dentry of another inode which is
	 * in the log but not yet processed since it has a higher inode number.
	 * So delete that other dentry.
	 */
	btrfs_dir_item_key_to_cpu(path->nodes[0], dir_item, &key);
	btrfs_release_path(path);
	other_inode = read_one_inode(root, key.objectid);
	if (!other_inode) {
		ret = -ENOENT;
		goto out;
	}
	ret = btrfs_unlink_inode(trans, root, BTRFS_I(dir), BTRFS_I(other_inode),
				 name, namelen);
	if (ret)
		goto out;
	/*
	 * If we dropped the link count to 0, bump it so that later the iput()
	 * on the inode will not free it. We will fixup the link count later.
	 */
	if (other_inode->i_nlink == 0)
		inc_nlink(other_inode);

	ret = btrfs_run_delayed_items(trans);
	if (ret)
		goto out;
add_link:
	ret = btrfs_add_link(trans, BTRFS_I(dir), BTRFS_I(inode),
			     name, namelen, 0, ref_index);
out:
	iput(other_inode);
	btrfs_free_path(path);

	return ret;
}