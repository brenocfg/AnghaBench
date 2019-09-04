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
struct send_ctx {int /*<<< orphan*/  parent_root; } ;
struct fs_path {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 int __get_cur_name_and_parent (struct send_ctx*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 
 int get_first_ref (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,struct fs_path*) ; 
 scalar_t__ is_waiting_for_move (struct send_ctx*,scalar_t__) ; 
 scalar_t__ is_waiting_for_rm (struct send_ctx*,scalar_t__) ; 

__attribute__((used)) static int path_loop(struct send_ctx *sctx, struct fs_path *name,
		     u64 ino, u64 gen, u64 *ancestor_ino)
{
	int ret = 0;
	u64 parent_inode = 0;
	u64 parent_gen = 0;
	u64 start_ino = ino;

	*ancestor_ino = 0;
	while (ino != BTRFS_FIRST_FREE_OBJECTID) {
		fs_path_reset(name);

		if (is_waiting_for_rm(sctx, ino))
			break;
		if (is_waiting_for_move(sctx, ino)) {
			if (*ancestor_ino == 0)
				*ancestor_ino = ino;
			ret = get_first_ref(sctx->parent_root, ino,
					    &parent_inode, &parent_gen, name);
		} else {
			ret = __get_cur_name_and_parent(sctx, ino, gen,
							&parent_inode,
							&parent_gen, name);
			if (ret > 0) {
				ret = 0;
				break;
			}
		}
		if (ret < 0)
			break;
		if (parent_inode == start_ino) {
			ret = 1;
			if (*ancestor_ino == 0)
				*ancestor_ino = ino;
			break;
		}
		ino = parent_inode;
		gen = parent_gen;
	}
	return ret;
}