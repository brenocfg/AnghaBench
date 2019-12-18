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
struct send_ctx {scalar_t__ cur_ino; int /*<<< orphan*/  deleted_refs; int /*<<< orphan*/  new_refs; int /*<<< orphan*/  cur_inode_gen; int /*<<< orphan*/  parent_root; int /*<<< orphan*/  send_root; } ;
struct recorded_ref {scalar_t__ dir; scalar_t__ dir_gen; } ;
struct fs_path {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 int ENOENT ; 
 int ENOMEM ; 
 int add_pending_dir_move (struct send_ctx*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int fs_path_len (struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 
 int get_first_ref (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,struct fs_path*) ; 
 int get_inode_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int is_ancestor (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct fs_path*) ; 
 scalar_t__ is_waiting_for_move (struct send_ctx*,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wait_for_parent_move(struct send_ctx *sctx,
				struct recorded_ref *parent_ref,
				const bool is_orphan)
{
	int ret = 0;
	u64 ino = parent_ref->dir;
	u64 ino_gen = parent_ref->dir_gen;
	u64 parent_ino_before, parent_ino_after;
	struct fs_path *path_before = NULL;
	struct fs_path *path_after = NULL;
	int len1, len2;

	path_after = fs_path_alloc();
	path_before = fs_path_alloc();
	if (!path_after || !path_before) {
		ret = -ENOMEM;
		goto out;
	}

	/*
	 * Our current directory inode may not yet be renamed/moved because some
	 * ancestor (immediate or not) has to be renamed/moved first. So find if
	 * such ancestor exists and make sure our own rename/move happens after
	 * that ancestor is processed to avoid path build infinite loops (done
	 * at get_cur_path()).
	 */
	while (ino > BTRFS_FIRST_FREE_OBJECTID) {
		u64 parent_ino_after_gen;

		if (is_waiting_for_move(sctx, ino)) {
			/*
			 * If the current inode is an ancestor of ino in the
			 * parent root, we need to delay the rename of the
			 * current inode, otherwise don't delayed the rename
			 * because we can end up with a circular dependency
			 * of renames, resulting in some directories never
			 * getting the respective rename operations issued in
			 * the send stream or getting into infinite path build
			 * loops.
			 */
			ret = is_ancestor(sctx->parent_root,
					  sctx->cur_ino, sctx->cur_inode_gen,
					  ino, path_before);
			if (ret)
				break;
		}

		fs_path_reset(path_before);
		fs_path_reset(path_after);

		ret = get_first_ref(sctx->send_root, ino, &parent_ino_after,
				    &parent_ino_after_gen, path_after);
		if (ret < 0)
			goto out;
		ret = get_first_ref(sctx->parent_root, ino, &parent_ino_before,
				    NULL, path_before);
		if (ret < 0 && ret != -ENOENT) {
			goto out;
		} else if (ret == -ENOENT) {
			ret = 0;
			break;
		}

		len1 = fs_path_len(path_before);
		len2 = fs_path_len(path_after);
		if (ino > sctx->cur_ino &&
		    (parent_ino_before != parent_ino_after || len1 != len2 ||
		     memcmp(path_before->start, path_after->start, len1))) {
			u64 parent_ino_gen;

			ret = get_inode_info(sctx->parent_root, ino, NULL,
					     &parent_ino_gen, NULL, NULL, NULL,
					     NULL);
			if (ret < 0)
				goto out;
			if (ino_gen == parent_ino_gen) {
				ret = 1;
				break;
			}
		}
		ino = parent_ino_after;
		ino_gen = parent_ino_after_gen;
	}

out:
	fs_path_free(path_before);
	fs_path_free(path_after);

	if (ret == 1) {
		ret = add_pending_dir_move(sctx,
					   sctx->cur_ino,
					   sctx->cur_inode_gen,
					   ino,
					   &sctx->new_refs,
					   &sctx->deleted_refs,
					   is_orphan);
		if (!ret)
			ret = 1;
	}

	return ret;
}