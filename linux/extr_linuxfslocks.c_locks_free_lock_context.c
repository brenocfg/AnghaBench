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
struct inode {struct file_lock_context* i_flctx; } ;
struct file_lock_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flctx_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct file_lock_context*) ; 
 int /*<<< orphan*/  locks_check_ctx_lists (struct inode*) ; 
 scalar_t__ unlikely (struct file_lock_context*) ; 

void
locks_free_lock_context(struct inode *inode)
{
	struct file_lock_context *ctx = inode->i_flctx;

	if (unlikely(ctx)) {
		locks_check_ctx_lists(inode);
		kmem_cache_free(flctx_cache, ctx);
	}
}