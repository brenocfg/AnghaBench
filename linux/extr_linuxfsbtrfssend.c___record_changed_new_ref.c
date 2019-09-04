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
struct send_ctx {int /*<<< orphan*/  cmp_key; int /*<<< orphan*/  right_path; int /*<<< orphan*/  parent_root; int /*<<< orphan*/  send_root; } ;
struct fs_path {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int __record_new_ref (int,int /*<<< orphan*/ ,int,struct fs_path*,struct send_ctx*) ; 
 int find_iref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int get_inode_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __record_changed_new_ref(int num, u64 dir, int index,
				    struct fs_path *name,
				    void *ctx)
{
	u64 dir_gen;
	int ret;
	struct send_ctx *sctx = ctx;

	ret = get_inode_info(sctx->send_root, dir, NULL, &dir_gen, NULL,
			     NULL, NULL, NULL);
	if (ret)
		return ret;

	ret = find_iref(sctx->parent_root, sctx->right_path,
			sctx->cmp_key, dir, dir_gen, name);
	if (ret == -ENOENT)
		ret = __record_new_ref(num, dir, index, name, sctx);
	else if (ret > 0)
		ret = 0;

	return ret;
}