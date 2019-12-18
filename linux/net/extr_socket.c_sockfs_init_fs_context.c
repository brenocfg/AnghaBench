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
struct pseudo_fs_context {int /*<<< orphan*/  xattr; int /*<<< orphan*/ * dops; int /*<<< orphan*/ * ops; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SOCKFS_MAGIC ; 
 struct pseudo_fs_context* init_pseudo (struct fs_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockfs_dentry_operations ; 
 int /*<<< orphan*/  sockfs_ops ; 
 int /*<<< orphan*/  sockfs_xattr_handlers ; 

__attribute__((used)) static int sockfs_init_fs_context(struct fs_context *fc)
{
	struct pseudo_fs_context *ctx = init_pseudo(fc, SOCKFS_MAGIC);
	if (!ctx)
		return -ENOMEM;
	ctx->ops = &sockfs_ops;
	ctx->dops = &sockfs_dentry_operations;
	ctx->xattr = sockfs_xattr_handlers;
	return 0;
}