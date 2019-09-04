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
typedef  void* u64 ;
struct fs_path {int dummy; } ;
struct find_ref_ctx {int found_idx; struct btrfs_root* root; void* dir_gen; struct fs_path* name; void* dir; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __find_iref ; 
 int iterate_inode_ref (struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct find_ref_ctx*) ; 

__attribute__((used)) static int find_iref(struct btrfs_root *root,
		     struct btrfs_path *path,
		     struct btrfs_key *key,
		     u64 dir, u64 dir_gen, struct fs_path *name)
{
	int ret;
	struct find_ref_ctx ctx;

	ctx.dir = dir;
	ctx.name = name;
	ctx.dir_gen = dir_gen;
	ctx.found_idx = -1;
	ctx.root = root;

	ret = iterate_inode_ref(root, path, key, 0, __find_iref, &ctx);
	if (ret < 0)
		return ret;

	if (ctx.found_idx == -1)
		return -ENOENT;

	return ctx.found_idx;
}