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
typedef  void* u64 ;
typedef  unsigned long u32 ;
struct inode {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ offset; int /*<<< orphan*/  type; } ;
struct btrfs_inode_ref {int dummy; } ;
struct btrfs_inode_extref {int /*<<< orphan*/  name; } ;
struct btrfs_inode {int /*<<< orphan*/  vfs_inode; } ;
struct btrfs_dir_item {int dummy; } ;

/* Variables and functions */
 struct btrfs_inode* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_EXTREF_KEY ; 
 int /*<<< orphan*/  BTRFS_INODE_REF_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IS_ERR (struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct btrfs_inode_extref*) ; 
 int /*<<< orphan*/  backref_in_log (struct btrfs_root*,struct btrfs_key*,void*,char*,int) ; 
 scalar_t__ btrfs_extref_hash (void*,char*,int) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int btrfs_inode_extref_name_len (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 void* btrfs_inode_extref_parent (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 int btrfs_inode_ref_name_len (struct extent_buffer*,struct btrfs_inode_ref*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 unsigned long btrfs_item_size_nr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 struct btrfs_dir_item* btrfs_lookup_dir_index_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,void*,char*,int,int /*<<< orphan*/ ) ; 
 struct btrfs_dir_item* btrfs_lookup_dir_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct btrfs_inode_extref* btrfs_lookup_inode_extref (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_path*,char*,int,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_run_delayed_items (struct btrfs_trans_handle*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_unlink_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_inode*,struct btrfs_inode*,char*,int) ; 
 int drop_one_dir_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_inode*,struct btrfs_dir_item*) ; 
 int /*<<< orphan*/  inc_nlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,char*,unsigned long,int) ; 
 struct inode* read_one_inode (struct btrfs_root*,void*) ; 

__attribute__((used)) static inline int __add_inode_ref(struct btrfs_trans_handle *trans,
				  struct btrfs_root *root,
				  struct btrfs_path *path,
				  struct btrfs_root *log_root,
				  struct btrfs_inode *dir,
				  struct btrfs_inode *inode,
				  u64 inode_objectid, u64 parent_objectid,
				  u64 ref_index, char *name, int namelen,
				  int *search_done)
{
	int ret;
	char *victim_name;
	int victim_name_len;
	struct extent_buffer *leaf;
	struct btrfs_dir_item *di;
	struct btrfs_key search_key;
	struct btrfs_inode_extref *extref;

again:
	/* Search old style refs */
	search_key.objectid = inode_objectid;
	search_key.type = BTRFS_INODE_REF_KEY;
	search_key.offset = parent_objectid;
	ret = btrfs_search_slot(NULL, root, &search_key, path, 0, 0);
	if (ret == 0) {
		struct btrfs_inode_ref *victim_ref;
		unsigned long ptr;
		unsigned long ptr_end;

		leaf = path->nodes[0];

		/* are we trying to overwrite a back ref for the root directory
		 * if so, just jump out, we're done
		 */
		if (search_key.objectid == search_key.offset)
			return 1;

		/* check all the names in this back reference to see
		 * if they are in the log.  if so, we allow them to stay
		 * otherwise they must be unlinked as a conflict
		 */
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		ptr_end = ptr + btrfs_item_size_nr(leaf, path->slots[0]);
		while (ptr < ptr_end) {
			victim_ref = (struct btrfs_inode_ref *)ptr;
			victim_name_len = btrfs_inode_ref_name_len(leaf,
								   victim_ref);
			victim_name = kmalloc(victim_name_len, GFP_NOFS);
			if (!victim_name)
				return -ENOMEM;

			read_extent_buffer(leaf, victim_name,
					   (unsigned long)(victim_ref + 1),
					   victim_name_len);

			if (!backref_in_log(log_root, &search_key,
					    parent_objectid,
					    victim_name,
					    victim_name_len)) {
				inc_nlink(&inode->vfs_inode);
				btrfs_release_path(path);

				ret = btrfs_unlink_inode(trans, root, dir, inode,
						victim_name, victim_name_len);
				kfree(victim_name);
				if (ret)
					return ret;
				ret = btrfs_run_delayed_items(trans);
				if (ret)
					return ret;
				*search_done = 1;
				goto again;
			}
			kfree(victim_name);

			ptr = (unsigned long)(victim_ref + 1) + victim_name_len;
		}

		/*
		 * NOTE: we have searched root tree and checked the
		 * corresponding ref, it does not need to check again.
		 */
		*search_done = 1;
	}
	btrfs_release_path(path);

	/* Same search but for extended refs */
	extref = btrfs_lookup_inode_extref(NULL, root, path, name, namelen,
					   inode_objectid, parent_objectid, 0,
					   0);
	if (!IS_ERR_OR_NULL(extref)) {
		u32 item_size;
		u32 cur_offset = 0;
		unsigned long base;
		struct inode *victim_parent;

		leaf = path->nodes[0];

		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		base = btrfs_item_ptr_offset(leaf, path->slots[0]);

		while (cur_offset < item_size) {
			extref = (struct btrfs_inode_extref *)(base + cur_offset);

			victim_name_len = btrfs_inode_extref_name_len(leaf, extref);

			if (btrfs_inode_extref_parent(leaf, extref) != parent_objectid)
				goto next;

			victim_name = kmalloc(victim_name_len, GFP_NOFS);
			if (!victim_name)
				return -ENOMEM;
			read_extent_buffer(leaf, victim_name, (unsigned long)&extref->name,
					   victim_name_len);

			search_key.objectid = inode_objectid;
			search_key.type = BTRFS_INODE_EXTREF_KEY;
			search_key.offset = btrfs_extref_hash(parent_objectid,
							      victim_name,
							      victim_name_len);
			ret = 0;
			if (!backref_in_log(log_root, &search_key,
					    parent_objectid, victim_name,
					    victim_name_len)) {
				ret = -ENOENT;
				victim_parent = read_one_inode(root,
						parent_objectid);
				if (victim_parent) {
					inc_nlink(&inode->vfs_inode);
					btrfs_release_path(path);

					ret = btrfs_unlink_inode(trans, root,
							BTRFS_I(victim_parent),
							inode,
							victim_name,
							victim_name_len);
					if (!ret)
						ret = btrfs_run_delayed_items(
								  trans);
				}
				iput(victim_parent);
				kfree(victim_name);
				if (ret)
					return ret;
				*search_done = 1;
				goto again;
			}
			kfree(victim_name);
next:
			cur_offset += victim_name_len + sizeof(*extref);
		}
		*search_done = 1;
	}
	btrfs_release_path(path);

	/* look for a conflicting sequence number */
	di = btrfs_lookup_dir_index_item(trans, root, path, btrfs_ino(dir),
					 ref_index, name, namelen, 0);
	if (di && !IS_ERR(di)) {
		ret = drop_one_dir_item(trans, root, path, dir, di);
		if (ret)
			return ret;
	}
	btrfs_release_path(path);

	/* look for a conflicting name */
	di = btrfs_lookup_dir_item(trans, root, path, btrfs_ino(dir),
				   name, namelen, 0);
	if (di && !IS_ERR(di)) {
		ret = drop_one_dir_item(trans, root, path, dir, di);
		if (ret)
			return ret;
	}
	btrfs_release_path(path);

	return 0;
}