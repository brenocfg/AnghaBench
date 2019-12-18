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
struct inode {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ type; int /*<<< orphan*/  offset; } ;
struct btrfs_inode_ref {int dummy; } ;
struct btrfs_inode_extref {int dummy; } ;
struct btrfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 scalar_t__ BTRFS_INODE_EXTREF_KEY ; 
 int ENOENT ; 
 int /*<<< orphan*/  btrfs_find_name_in_backref (struct extent_buffer*,int,char*,int) ; 
 int /*<<< orphan*/  btrfs_find_name_in_ext_backref (struct extent_buffer*,int,int /*<<< orphan*/ ,char*,int) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 unsigned long btrfs_item_size_nr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_unlink_inode (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,struct btrfs_inode*,char*,int) ; 
 int extref_get_fields (struct extent_buffer*,unsigned long,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct inode* read_one_inode (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int ref_get_fields (struct extent_buffer*,unsigned long,int*,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unlink_old_inode_refs(struct btrfs_trans_handle *trans,
				 struct btrfs_root *root,
				 struct btrfs_path *path,
				 struct btrfs_inode *inode,
				 struct extent_buffer *log_eb,
				 int log_slot,
				 struct btrfs_key *key)
{
	int ret;
	unsigned long ref_ptr;
	unsigned long ref_end;
	struct extent_buffer *eb;

again:
	btrfs_release_path(path);
	ret = btrfs_search_slot(NULL, root, key, path, 0, 0);
	if (ret > 0) {
		ret = 0;
		goto out;
	}
	if (ret < 0)
		goto out;

	eb = path->nodes[0];
	ref_ptr = btrfs_item_ptr_offset(eb, path->slots[0]);
	ref_end = ref_ptr + btrfs_item_size_nr(eb, path->slots[0]);
	while (ref_ptr < ref_end) {
		char *name = NULL;
		int namelen;
		u64 parent_id;

		if (key->type == BTRFS_INODE_EXTREF_KEY) {
			ret = extref_get_fields(eb, ref_ptr, &namelen, &name,
						NULL, &parent_id);
		} else {
			parent_id = key->offset;
			ret = ref_get_fields(eb, ref_ptr, &namelen, &name,
					     NULL);
		}
		if (ret)
			goto out;

		if (key->type == BTRFS_INODE_EXTREF_KEY)
			ret = !!btrfs_find_name_in_ext_backref(log_eb, log_slot,
							       parent_id, name,
							       namelen);
		else
			ret = !!btrfs_find_name_in_backref(log_eb, log_slot,
							   name, namelen);

		if (!ret) {
			struct inode *dir;

			btrfs_release_path(path);
			dir = read_one_inode(root, parent_id);
			if (!dir) {
				ret = -ENOENT;
				kfree(name);
				goto out;
			}
			ret = btrfs_unlink_inode(trans, root, BTRFS_I(dir),
						 inode, name, namelen);
			kfree(name);
			iput(dir);
			if (ret)
				goto out;
			goto again;
		}

		kfree(name);
		ref_ptr += namelen;
		if (key->type == BTRFS_INODE_EXTREF_KEY)
			ref_ptr += sizeof(struct btrfs_inode_extref);
		else
			ref_ptr += sizeof(struct btrfs_inode_ref);
	}
	ret = 0;
 out:
	btrfs_release_path(path);
	return ret;
}