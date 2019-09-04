#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {struct extent_buffer** nodes; } ;
struct btrfs_dir_item {int dummy; } ;
struct TYPE_3__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int ENODATA ; 
 int ENOMEM ; 
 int ERANGE ; 
 scalar_t__ IS_ERR (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 size_t btrfs_dir_data_len (struct extent_buffer*,struct btrfs_dir_item*) ; 
 int btrfs_dir_name_len (struct extent_buffer*,struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_ino (TYPE_1__*) ; 
 struct btrfs_dir_item* btrfs_lookup_xattr (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,void*,unsigned long,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int btrfs_getxattr(struct inode *inode, const char *name,
				void *buffer, size_t size)
{
	struct btrfs_dir_item *di;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_path *path;
	struct extent_buffer *leaf;
	int ret = 0;
	unsigned long data_ptr;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	/* lookup the xattr by name */
	di = btrfs_lookup_xattr(NULL, root, path, btrfs_ino(BTRFS_I(inode)),
			name, strlen(name), 0);
	if (!di) {
		ret = -ENODATA;
		goto out;
	} else if (IS_ERR(di)) {
		ret = PTR_ERR(di);
		goto out;
	}

	leaf = path->nodes[0];
	/* if size is 0, that means we want the size of the attr */
	if (!size) {
		ret = btrfs_dir_data_len(leaf, di);
		goto out;
	}

	/* now get the data out of our dir_item */
	if (btrfs_dir_data_len(leaf, di) > size) {
		ret = -ERANGE;
		goto out;
	}

	/*
	 * The way things are packed into the leaf is like this
	 * |struct btrfs_dir_item|name|data|
	 * where name is the xattr name, so security.foo, and data is the
	 * content of the xattr.  data_ptr points to the location in memory
	 * where the data starts in the in memory leaf
	 */
	data_ptr = (unsigned long)((char *)(di + 1) +
				   btrfs_dir_name_len(leaf, di));
	read_extent_buffer(leaf, buffer, data_ptr,
			   btrfs_dir_data_len(leaf, di));
	ret = btrfs_dir_data_len(leaf, di);

out:
	btrfs_free_path(path);
	return ret;
}