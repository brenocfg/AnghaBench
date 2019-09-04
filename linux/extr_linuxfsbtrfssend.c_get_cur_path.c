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
struct waiting_dir_move {scalar_t__ orphanized; } ;
struct send_ctx {int /*<<< orphan*/  parent_root; } ;
struct fs_path {int reversed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FIRST_FREE_OBJECTID ; 
 int ENOMEM ; 
 int __get_cur_name_and_parent (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fs_path*) ; 
 int fs_path_add_path (struct fs_path*,struct fs_path*) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_unreverse (struct fs_path*) ; 
 int gen_unique_name (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int get_first_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fs_path*) ; 
 struct waiting_dir_move* get_waiting_dir_move (struct send_ctx*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_waiting_for_rm (struct send_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_cur_path(struct send_ctx *sctx, u64 ino, u64 gen,
			struct fs_path *dest)
{
	int ret = 0;
	struct fs_path *name = NULL;
	u64 parent_inode = 0;
	u64 parent_gen = 0;
	int stop = 0;

	name = fs_path_alloc();
	if (!name) {
		ret = -ENOMEM;
		goto out;
	}

	dest->reversed = 1;
	fs_path_reset(dest);

	while (!stop && ino != BTRFS_FIRST_FREE_OBJECTID) {
		struct waiting_dir_move *wdm;

		fs_path_reset(name);

		if (is_waiting_for_rm(sctx, ino)) {
			ret = gen_unique_name(sctx, ino, gen, name);
			if (ret < 0)
				goto out;
			ret = fs_path_add_path(dest, name);
			break;
		}

		wdm = get_waiting_dir_move(sctx, ino);
		if (wdm && wdm->orphanized) {
			ret = gen_unique_name(sctx, ino, gen, name);
			stop = 1;
		} else if (wdm) {
			ret = get_first_ref(sctx->parent_root, ino,
					    &parent_inode, &parent_gen, name);
		} else {
			ret = __get_cur_name_and_parent(sctx, ino, gen,
							&parent_inode,
							&parent_gen, name);
			if (ret)
				stop = 1;
		}

		if (ret < 0)
			goto out;

		ret = fs_path_add_path(dest, name);
		if (ret < 0)
			goto out;

		ino = parent_inode;
		gen = parent_gen;
	}

out:
	fs_path_free(name);
	if (!ret)
		fs_path_unreverse(dest);
	return ret;
}