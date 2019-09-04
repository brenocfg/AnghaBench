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
struct send_ctx {int /*<<< orphan*/  right_path; int /*<<< orphan*/  parent_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  __process_deleted_xattr ; 
 int iterate_dir_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct send_ctx*) ; 

__attribute__((used)) static int process_deleted_xattr(struct send_ctx *sctx)
{
	return iterate_dir_item(sctx->parent_root, sctx->right_path,
				__process_deleted_xattr, sctx);
}