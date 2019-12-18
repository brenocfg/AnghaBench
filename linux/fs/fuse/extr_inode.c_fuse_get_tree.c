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
struct fuse_fs_context {scalar_t__ is_bdev; int /*<<< orphan*/  group_id_present; int /*<<< orphan*/  user_id_present; int /*<<< orphan*/  rootmode_present; int /*<<< orphan*/  fd_present; } ;
struct fs_context {struct fuse_fs_context* fs_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fuse_fill_super ; 
 int get_tree_bdev (struct fs_context*,int /*<<< orphan*/ ) ; 
 int get_tree_nodev (struct fs_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_get_tree(struct fs_context *fc)
{
	struct fuse_fs_context *ctx = fc->fs_private;

	if (!ctx->fd_present || !ctx->rootmode_present ||
	    !ctx->user_id_present || !ctx->group_id_present)
		return -EINVAL;

#ifdef CONFIG_BLOCK
	if (ctx->is_bdev)
		return get_tree_bdev(fc, fuse_fill_super);
#endif

	return get_tree_nodev(fc, fuse_fill_super);
}