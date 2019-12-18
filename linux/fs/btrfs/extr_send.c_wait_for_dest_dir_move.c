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
typedef  scalar_t__ u64 ;
struct waiting_dir_move {int /*<<< orphan*/  orphanized; } ;
struct send_ctx {int /*<<< orphan*/  deleted_refs; int /*<<< orphan*/  new_refs; int /*<<< orphan*/  cur_inode_gen; int /*<<< orphan*/  cur_ino; TYPE_1__* send_root; TYPE_1__* parent_root; int /*<<< orphan*/  waiting_dir_moves; } ;
struct recorded_ref {int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  dir; } ;
struct btrfs_path {int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ type; int /*<<< orphan*/  objectid; int /*<<< orphan*/  offset; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_dir_item {int dummy; } ;
struct TYPE_3__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 scalar_t__ BTRFS_DIR_ITEM_KEY ; 
 scalar_t__ BTRFS_INODE_ITEM_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int add_pending_dir_move (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 struct btrfs_path* alloc_path_for_send () ; 
 int /*<<< orphan*/  btrfs_dir_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_dir_item*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 struct btrfs_dir_item* btrfs_match_dir_item_name (struct btrfs_fs_info*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_name_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,TYPE_1__*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_inode_info (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct waiting_dir_move* get_waiting_dir_move (struct send_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_for_dest_dir_move(struct send_ctx *sctx,
				  struct recorded_ref *parent_ref,
				  const bool is_orphan)
{
	struct btrfs_fs_info *fs_info = sctx->parent_root->fs_info;
	struct btrfs_path *path;
	struct btrfs_key key;
	struct btrfs_key di_key;
	struct btrfs_dir_item *di;
	u64 left_gen;
	u64 right_gen;
	int ret = 0;
	struct waiting_dir_move *wdm;

	if (RB_EMPTY_ROOT(&sctx->waiting_dir_moves))
		return 0;

	path = alloc_path_for_send();
	if (!path)
		return -ENOMEM;

	key.objectid = parent_ref->dir;
	key.type = BTRFS_DIR_ITEM_KEY;
	key.offset = btrfs_name_hash(parent_ref->name, parent_ref->name_len);

	ret = btrfs_search_slot(NULL, sctx->parent_root, &key, path, 0, 0);
	if (ret < 0) {
		goto out;
	} else if (ret > 0) {
		ret = 0;
		goto out;
	}

	di = btrfs_match_dir_item_name(fs_info, path, parent_ref->name,
				       parent_ref->name_len);
	if (!di) {
		ret = 0;
		goto out;
	}
	/*
	 * di_key.objectid has the number of the inode that has a dentry in the
	 * parent directory with the same name that sctx->cur_ino is being
	 * renamed to. We need to check if that inode is in the send root as
	 * well and if it is currently marked as an inode with a pending rename,
	 * if it is, we need to delay the rename of sctx->cur_ino as well, so
	 * that it happens after that other inode is renamed.
	 */
	btrfs_dir_item_key_to_cpu(path->nodes[0], di, &di_key);
	if (di_key.type != BTRFS_INODE_ITEM_KEY) {
		ret = 0;
		goto out;
	}

	ret = get_inode_info(sctx->parent_root, di_key.objectid, NULL,
			     &left_gen, NULL, NULL, NULL, NULL);
	if (ret < 0)
		goto out;
	ret = get_inode_info(sctx->send_root, di_key.objectid, NULL,
			     &right_gen, NULL, NULL, NULL, NULL);
	if (ret < 0) {
		if (ret == -ENOENT)
			ret = 0;
		goto out;
	}

	/* Different inode, no need to delay the rename of sctx->cur_ino */
	if (right_gen != left_gen) {
		ret = 0;
		goto out;
	}

	wdm = get_waiting_dir_move(sctx, di_key.objectid);
	if (wdm && !wdm->orphanized) {
		ret = add_pending_dir_move(sctx,
					   sctx->cur_ino,
					   sctx->cur_inode_gen,
					   di_key.objectid,
					   &sctx->new_refs,
					   &sctx->deleted_refs,
					   is_orphan);
		if (!ret)
			ret = 1;
	}
out:
	btrfs_free_path(path);
	return ret;
}