#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct send_ctx {TYPE_1__* cmp_key; struct btrfs_root* send_root; struct btrfs_root* parent_root; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  iterate_inode_ref_t ;
typedef  enum btrfs_compare_tree_result { ____Placeholder_btrfs_compare_tree_result } btrfs_compare_tree_result ;
struct TYPE_2__ {scalar_t__ objectid; } ;

/* Variables and functions */
 int BTRFS_COMPARE_TREE_DELETED ; 
 int BTRFS_COMPARE_TREE_NEW ; 
 scalar_t__ BTRFS_INODE_EXTREF_KEY ; 
 scalar_t__ BTRFS_INODE_REF_KEY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __record_deleted_ref ; 
 int /*<<< orphan*/  __record_new_ref ; 
 struct btrfs_path* alloc_path_for_send () ; 
 int /*<<< orphan*/  btrfs_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int btrfs_next_leaf (struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iterate_inode_ref (struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct send_ctx*) ; 
 int process_recorded_refs (struct send_ctx*,int*) ; 

__attribute__((used)) static int process_all_refs(struct send_ctx *sctx,
			    enum btrfs_compare_tree_result cmd)
{
	int ret;
	struct btrfs_root *root;
	struct btrfs_path *path;
	struct btrfs_key key;
	struct btrfs_key found_key;
	struct extent_buffer *eb;
	int slot;
	iterate_inode_ref_t cb;
	int pending_move = 0;

	path = alloc_path_for_send();
	if (!path)
		return -ENOMEM;

	if (cmd == BTRFS_COMPARE_TREE_NEW) {
		root = sctx->send_root;
		cb = __record_new_ref;
	} else if (cmd == BTRFS_COMPARE_TREE_DELETED) {
		root = sctx->parent_root;
		cb = __record_deleted_ref;
	} else {
		btrfs_err(sctx->send_root->fs_info,
				"Wrong command %d in process_all_refs", cmd);
		ret = -EINVAL;
		goto out;
	}

	key.objectid = sctx->cmp_key->objectid;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
	if (ret < 0)
		goto out;

	while (1) {
		eb = path->nodes[0];
		slot = path->slots[0];
		if (slot >= btrfs_header_nritems(eb)) {
			ret = btrfs_next_leaf(root, path);
			if (ret < 0)
				goto out;
			else if (ret > 0)
				break;
			continue;
		}

		btrfs_item_key_to_cpu(eb, &found_key, slot);

		if (found_key.objectid != key.objectid ||
		    (found_key.type != BTRFS_INODE_REF_KEY &&
		     found_key.type != BTRFS_INODE_EXTREF_KEY))
			break;

		ret = iterate_inode_ref(root, path, &found_key, 0, cb, sctx);
		if (ret < 0)
			goto out;

		path->slots[0]++;
	}
	btrfs_release_path(path);

	/*
	 * We don't actually care about pending_move as we are simply
	 * re-creating this inode and will be rename'ing it into place once we
	 * rename the parent directory.
	 */
	ret = process_recorded_refs(sctx, &pending_move);
out:
	btrfs_free_path(path);
	return ret;
}