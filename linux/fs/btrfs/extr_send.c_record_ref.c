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
struct send_ctx {int dummy; } ;
struct list_head {int dummy; } ;
struct fs_path {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __record_ref (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int fs_path_add_path (struct fs_path*,struct fs_path*) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int get_cur_path (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int get_inode_info (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int record_ref(struct btrfs_root *root, u64 dir, struct fs_path *name,
		      void *ctx, struct list_head *refs)
{
	int ret = 0;
	struct send_ctx *sctx = ctx;
	struct fs_path *p;
	u64 gen;

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

	ret = get_inode_info(root, dir, NULL, &gen, NULL, NULL,
			NULL, NULL);
	if (ret < 0)
		goto out;

	ret = get_cur_path(sctx, dir, gen, p);
	if (ret < 0)
		goto out;
	ret = fs_path_add_path(p, name);
	if (ret < 0)
		goto out;

	ret = __record_ref(refs, dir, gen, p);

out:
	if (ret)
		fs_path_free(p);
	return ret;
}