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
struct fs_path {int /*<<< orphan*/  start; } ;
struct find_ref_ctx {scalar_t__ dir; scalar_t__ dir_gen; int found_idx; int /*<<< orphan*/  root; struct fs_path* name; } ;

/* Variables and functions */
 scalar_t__ fs_path_len (struct fs_path*) ; 
 int get_inode_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __find_iref(int num, u64 dir, int index,
		       struct fs_path *name,
		       void *ctx_)
{
	struct find_ref_ctx *ctx = ctx_;
	u64 dir_gen;
	int ret;

	if (dir == ctx->dir && fs_path_len(name) == fs_path_len(ctx->name) &&
	    strncmp(name->start, ctx->name->start, fs_path_len(name)) == 0) {
		/*
		 * To avoid doing extra lookups we'll only do this if everything
		 * else matches.
		 */
		ret = get_inode_info(ctx->root, dir, NULL, &dir_gen, NULL,
				     NULL, NULL, NULL);
		if (ret)
			return ret;
		if (dir_gen != ctx->dir_gen)
			return 0;
		ctx->found_idx = num;
		return 1;
	}
	return 0;
}