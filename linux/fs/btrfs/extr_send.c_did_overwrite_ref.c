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
struct send_ctx {scalar_t__ send_progress; scalar_t__ cur_ino; scalar_t__ cur_inode_gen; int /*<<< orphan*/  send_root; int /*<<< orphan*/  parent_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 int ENOENT ; 
 int get_inode_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int is_inode_existent (struct send_ctx*,scalar_t__,scalar_t__) ; 
 int lookup_dir_item_inode (int /*<<< orphan*/ ,scalar_t__,char const*,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int did_overwrite_ref(struct send_ctx *sctx,
			    u64 dir, u64 dir_gen,
			    u64 ino, u64 ino_gen,
			    const char *name, int name_len)
{
	int ret = 0;
	u64 gen;
	u64 ow_inode;
	u8 other_type;

	if (!sctx->parent_root)
		goto out;

	ret = is_inode_existent(sctx, dir, dir_gen);
	if (ret <= 0)
		goto out;

	if (dir != BTRFS_FIRST_FREE_OBJECTID) {
		ret = get_inode_info(sctx->send_root, dir, NULL, &gen, NULL,
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

	/* check if the ref was overwritten by another ref */
	ret = lookup_dir_item_inode(sctx->send_root, dir, name, name_len,
			&ow_inode, &other_type);
	if (ret < 0 && ret != -ENOENT)
		goto out;
	if (ret) {
		/* was never and will never be overwritten */
		ret = 0;
		goto out;
	}

	ret = get_inode_info(sctx->send_root, ow_inode, NULL, &gen, NULL, NULL,
			NULL, NULL);
	if (ret < 0)
		goto out;

	if (ow_inode == ino && gen == ino_gen) {
		ret = 0;
		goto out;
	}

	/*
	 * We know that it is or will be overwritten. Check this now.
	 * The current inode being processed might have been the one that caused
	 * inode 'ino' to be orphanized, therefore check if ow_inode matches
	 * the current inode being processed.
	 */
	if ((ow_inode < sctx->send_progress) ||
	    (ino != sctx->cur_ino && ow_inode == sctx->cur_ino &&
	     gen == sctx->cur_inode_gen))
		ret = 1;
	else
		ret = 0;

out:
	return ret;
}