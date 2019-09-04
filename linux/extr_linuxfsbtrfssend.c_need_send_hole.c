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
struct send_ctx {int /*<<< orphan*/  cur_inode_mode; int /*<<< orphan*/  cur_inode_deleted; int /*<<< orphan*/  cur_inode_new_gen; int /*<<< orphan*/  cur_inode_new; scalar_t__ parent_root; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int need_send_hole(struct send_ctx *sctx)
{
	return (sctx->parent_root && !sctx->cur_inode_new &&
		!sctx->cur_inode_new_gen && !sctx->cur_inode_deleted &&
		S_ISREG(sctx->cur_inode_mode));
}