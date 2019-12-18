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
struct fs_path {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ BTRFS_INODE_EXTREF_KEY ; 
 scalar_t__ BTRFS_INODE_REF_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __copy_first_ref ; 
 struct btrfs_path* alloc_path_for_send () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int btrfs_search_slot_for_read (struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 
 int iterate_inode_ref (struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int,int /*<<< orphan*/ ,struct fs_path*) ; 

__attribute__((used)) static int get_inode_path(struct btrfs_root *root,
			  u64 ino, struct fs_path *path)
{
	int ret;
	struct btrfs_key key, found_key;
	struct btrfs_path *p;

	p = alloc_path_for_send();
	if (!p)
		return -ENOMEM;

	fs_path_reset(path);

	key.objectid = ino;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;

	ret = btrfs_search_slot_for_read(root, &key, p, 1, 0);
	if (ret < 0)
		goto out;
	if (ret) {
		ret = 1;
		goto out;
	}
	btrfs_item_key_to_cpu(p->nodes[0], &found_key, p->slots[0]);
	if (found_key.objectid != ino ||
	    (found_key.type != BTRFS_INODE_REF_KEY &&
	     found_key.type != BTRFS_INODE_EXTREF_KEY)) {
		ret = -ENOENT;
		goto out;
	}

	ret = iterate_inode_ref(root, p, &found_key, 1,
				__copy_first_ref, path);
	if (ret < 0)
		goto out;
	ret = 0;

out:
	btrfs_free_path(p);
	return ret;
}