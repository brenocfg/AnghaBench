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
typedef  scalar_t__ u64 ;
struct send_ctx {scalar_t__ send_progress; scalar_t__ parent_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 int ENOENT ; 
 int get_inode_info (scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int is_inode_existent (struct send_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ is_waiting_for_move (struct send_ctx*,scalar_t__) ; 
 int lookup_dir_item_inode (scalar_t__,scalar_t__,char const*,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int will_overwrite_ref(struct send_ctx *sctx, u64 dir, u64 dir_gen,
			      const char *name, int name_len,
			      u64 *who_ino, u64 *who_gen, u64 *who_mode)
{
	int ret = 0;
	u64 gen;
	u64 other_inode = 0;
	u8 other_type = 0;

	if (!sctx->parent_root)
		goto out;

	ret = is_inode_existent(sctx, dir, dir_gen);
	if (ret <= 0)
		goto out;

	/*
	 * If we have a parent root we need to verify that the parent dir was
	 * not deleted and then re-created, if it was then we have no overwrite
	 * and we can just unlink this entry.
	 */
	if (sctx->parent_root && dir != BTRFS_FIRST_FREE_OBJECTID) {
		ret = get_inode_info(sctx->parent_root, dir, NULL, &gen, NULL,
				     NULL, NULL, NULL);
		if (ret < 0 && ret != -ENOENT)
			goto out;
		if (ret) {
			ret = 0;
			goto out;
		}
		if (gen != dir_gen)
			goto out;
	}

	ret = lookup_dir_item_inode(sctx->parent_root, dir, name, name_len,
			&other_inode, &other_type);
	if (ret < 0 && ret != -ENOENT)
		goto out;
	if (ret) {
		ret = 0;
		goto out;
	}

	/*
	 * Check if the overwritten ref was already processed. If yes, the ref
	 * was already unlinked/moved, so we can safely assume that we will not
	 * overwrite anything at this point in time.
	 */
	if (other_inode > sctx->send_progress ||
	    is_waiting_for_move(sctx, other_inode)) {
		ret = get_inode_info(sctx->parent_root, other_inode, NULL,
				who_gen, who_mode, NULL, NULL, NULL);
		if (ret < 0)
			goto out;

		ret = 1;
		*who_ino = other_inode;
	} else {
		ret = 0;
	}

out:
	return ret;
}