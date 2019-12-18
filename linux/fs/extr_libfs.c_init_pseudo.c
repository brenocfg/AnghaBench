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
struct pseudo_fs_context {unsigned long magic; } ;
struct fs_context {int global; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/ * ops; struct pseudo_fs_context* fs_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SB_NOUSER ; 
 struct pseudo_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct pseudo_fs_context*) ; 
 int /*<<< orphan*/  pseudo_fs_context_ops ; 

struct pseudo_fs_context *init_pseudo(struct fs_context *fc,
					unsigned long magic)
{
	struct pseudo_fs_context *ctx;

	ctx = kzalloc(sizeof(struct pseudo_fs_context), GFP_KERNEL);
	if (likely(ctx)) {
		ctx->magic = magic;
		fc->fs_private = ctx;
		fc->ops = &pseudo_fs_context_ops;
		fc->sb_flags |= SB_NOUSER;
		fc->global = true;
	}
	return ctx;
}