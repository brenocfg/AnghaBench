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
struct send_ctx {int /*<<< orphan*/  parent_root; int /*<<< orphan*/  send_root; } ;

/* Variables and functions */
 int get_inode_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dir_changed(struct send_ctx *sctx, u64 dir)
{
	u64 orig_gen, new_gen;
	int ret;

	ret = get_inode_info(sctx->send_root, dir, NULL, &new_gen, NULL, NULL,
			     NULL, NULL);
	if (ret)
		return ret;

	ret = get_inode_info(sctx->parent_root, dir, NULL, &orig_gen, NULL,
			     NULL, NULL, NULL);
	if (ret)
		return ret;

	return (orig_gen != new_gen) ? 1 : 0;
}