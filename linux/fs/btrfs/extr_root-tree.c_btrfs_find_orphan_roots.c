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
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  state; int /*<<< orphan*/  root_item; } ;
struct btrfs_path {scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
struct btrfs_fs_info {struct btrfs_root* tree_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_ORPHAN_ITEM_KEY ; 
 scalar_t__ BTRFS_ORPHAN_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_ROOT_DEAD_TREE ; 
 scalar_t__ BTRFS_ROOT_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_ROOT_ORPHAN_ITEM_INSERTED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR_OR_ZERO (struct btrfs_root*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_add_dead_root (struct btrfs_root*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_del_orphan_item (struct btrfs_trans_handle*,struct btrfs_root*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_free_fs_root (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_handle_fs_error (struct btrfs_fs_info*,int,char*) ; 
 scalar_t__ btrfs_header_nritems (struct extent_buffer*) ; 
 int btrfs_init_fs_root (struct btrfs_root*) ; 
 int btrfs_insert_fs_root (struct btrfs_fs_info*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,scalar_t__) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (struct btrfs_root*) ; 
 struct btrfs_root* btrfs_lookup_fs_root (struct btrfs_fs_info*,scalar_t__) ; 
 int btrfs_next_leaf (struct btrfs_root*,struct btrfs_path*) ; 
 struct btrfs_root* btrfs_read_fs_root (struct btrfs_root*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_find_orphan_roots(struct btrfs_fs_info *fs_info)
{
	struct btrfs_root *tree_root = fs_info->tree_root;
	struct extent_buffer *leaf;
	struct btrfs_path *path;
	struct btrfs_key key;
	struct btrfs_key root_key;
	struct btrfs_root *root;
	int err = 0;
	int ret;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = 0;

	root_key.type = BTRFS_ROOT_ITEM_KEY;
	root_key.offset = (u64)-1;

	while (1) {
		ret = btrfs_search_slot(NULL, tree_root, &key, path, 0, 0);
		if (ret < 0) {
			err = ret;
			break;
		}

		leaf = path->nodes[0];
		if (path->slots[0] >= btrfs_header_nritems(leaf)) {
			ret = btrfs_next_leaf(tree_root, path);
			if (ret < 0)
				err = ret;
			if (ret != 0)
				break;
			leaf = path->nodes[0];
		}

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		btrfs_release_path(path);

		if (key.objectid != BTRFS_ORPHAN_OBJECTID ||
		    key.type != BTRFS_ORPHAN_ITEM_KEY)
			break;

		root_key.objectid = key.offset;
		key.offset++;

		/*
		 * The root might have been inserted already, as before we look
		 * for orphan roots, log replay might have happened, which
		 * triggers a transaction commit and qgroup accounting, which
		 * in turn reads and inserts fs roots while doing backref
		 * walking.
		 */
		root = btrfs_lookup_fs_root(fs_info, root_key.objectid);
		if (root) {
			WARN_ON(!test_bit(BTRFS_ROOT_ORPHAN_ITEM_INSERTED,
					  &root->state));
			if (btrfs_root_refs(&root->root_item) == 0) {
				set_bit(BTRFS_ROOT_DEAD_TREE, &root->state);
				btrfs_add_dead_root(root);
			}
			continue;
		}

		root = btrfs_read_fs_root(tree_root, &root_key);
		err = PTR_ERR_OR_ZERO(root);
		if (err && err != -ENOENT) {
			break;
		} else if (err == -ENOENT) {
			struct btrfs_trans_handle *trans;

			btrfs_release_path(path);

			trans = btrfs_join_transaction(tree_root);
			if (IS_ERR(trans)) {
				err = PTR_ERR(trans);
				btrfs_handle_fs_error(fs_info, err,
					    "Failed to start trans to delete orphan item");
				break;
			}
			err = btrfs_del_orphan_item(trans, tree_root,
						    root_key.objectid);
			btrfs_end_transaction(trans);
			if (err) {
				btrfs_handle_fs_error(fs_info, err,
					    "Failed to delete root orphan item");
				break;
			}
			continue;
		}

		err = btrfs_init_fs_root(root);
		if (err) {
			btrfs_free_fs_root(root);
			break;
		}

		set_bit(BTRFS_ROOT_ORPHAN_ITEM_INSERTED, &root->state);

		err = btrfs_insert_fs_root(fs_info, root);
		if (err) {
			BUG_ON(err == -EEXIST);
			btrfs_free_fs_root(root);
			break;
		}

		if (btrfs_root_refs(&root->root_item) == 0) {
			set_bit(BTRFS_ROOT_DEAD_TREE, &root->state);
			btrfs_add_dead_root(root);
		}
	}

	btrfs_free_path(path);
	return err;
}