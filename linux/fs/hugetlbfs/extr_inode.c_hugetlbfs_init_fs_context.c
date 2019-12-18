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
struct hugetlbfs_fs_context {int max_hpages; int nr_inodes; int mode; int min_hpages; void* min_val_type; void* max_val_type; int /*<<< orphan*/ * hstate; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct hugetlbfs_fs_context* fs_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* NO_SIZE ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  default_hstate ; 
 int /*<<< orphan*/  hugetlbfs_fs_context_ops ; 
 struct hugetlbfs_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hugetlbfs_init_fs_context(struct fs_context *fc)
{
	struct hugetlbfs_fs_context *ctx;

	ctx = kzalloc(sizeof(struct hugetlbfs_fs_context), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->max_hpages	= -1; /* No limit on size by default */
	ctx->nr_inodes	= -1; /* No limit on number of inodes by default */
	ctx->uid	= current_fsuid();
	ctx->gid	= current_fsgid();
	ctx->mode	= 0755;
	ctx->hstate	= &default_hstate;
	ctx->min_hpages	= -1; /* No default minimum size */
	ctx->max_val_type = NO_SIZE;
	ctx->min_val_type = NO_SIZE;
	fc->fs_private = ctx;
	fc->ops	= &hugetlbfs_fs_context_ops;
	return 0;
}