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
struct send_ctx {int /*<<< orphan*/  right_path; int /*<<< orphan*/  parent_root; int /*<<< orphan*/  left_path; int /*<<< orphan*/  send_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  __process_changed_deleted_xattr ; 
 int /*<<< orphan*/  __process_changed_new_xattr ; 
 int iterate_dir_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct send_ctx*) ; 

__attribute__((used)) static int process_changed_xattr(struct send_ctx *sctx)
{
	int ret = 0;

	ret = iterate_dir_item(sctx->send_root, sctx->left_path,
			__process_changed_new_xattr, sctx);
	if (ret < 0)
		goto out;
	ret = iterate_dir_item(sctx->parent_root, sctx->right_path,
			__process_changed_deleted_xattr, sctx);

out:
	return ret;
}