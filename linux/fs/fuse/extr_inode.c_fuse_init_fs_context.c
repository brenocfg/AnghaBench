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
struct fuse_fs_context {int is_bdev; int destroy; int /*<<< orphan*/  blksize; int /*<<< orphan*/  max_read; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct fuse_fs_context* fs_private; int /*<<< orphan*/ * fs_type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FUSE_DEFAULT_BLKSIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fuse_context_ops ; 
 int /*<<< orphan*/  fuseblk_fs_type ; 
 struct fuse_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_init_fs_context(struct fs_context *fc)
{
	struct fuse_fs_context *ctx;

	ctx = kzalloc(sizeof(struct fuse_fs_context), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->max_read = ~0;
	ctx->blksize = FUSE_DEFAULT_BLKSIZE;

#ifdef CONFIG_BLOCK
	if (fc->fs_type == &fuseblk_fs_type) {
		ctx->is_bdev = true;
		ctx->destroy = true;
	}
#endif

	fc->fs_private = ctx;
	fc->ops = &fuse_context_ops;
	return 0;
}