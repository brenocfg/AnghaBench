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
struct inode {int /*<<< orphan*/  i_flctx; } ;
struct file_lock_context {int /*<<< orphan*/  flc_lease; int /*<<< orphan*/  flc_posix; int /*<<< orphan*/  flc_flock; int /*<<< orphan*/  flc_lock; } ;

/* Variables and functions */
 int F_UNLCK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct file_lock_context*) ; 
 int /*<<< orphan*/  flctx_cache ; 
 struct file_lock_context* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct file_lock_context*) ; 
 scalar_t__ likely (struct file_lock_context*) ; 
 struct file_lock_context* smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_locks_get_lock_context (struct inode*,int,struct file_lock_context*) ; 

__attribute__((used)) static struct file_lock_context *
locks_get_lock_context(struct inode *inode, int type)
{
	struct file_lock_context *ctx;

	/* paired with cmpxchg() below */
	ctx = smp_load_acquire(&inode->i_flctx);
	if (likely(ctx) || type == F_UNLCK)
		goto out;

	ctx = kmem_cache_alloc(flctx_cache, GFP_KERNEL);
	if (!ctx)
		goto out;

	spin_lock_init(&ctx->flc_lock);
	INIT_LIST_HEAD(&ctx->flc_flock);
	INIT_LIST_HEAD(&ctx->flc_posix);
	INIT_LIST_HEAD(&ctx->flc_lease);

	/*
	 * Assign the pointer if it's not already assigned. If it is, then
	 * free the context we just allocated.
	 */
	if (cmpxchg(&inode->i_flctx, NULL, ctx)) {
		kmem_cache_free(flctx_cache, ctx);
		ctx = smp_load_acquire(&inode->i_flctx);
	}
out:
	trace_locks_get_lock_context(inode, type, ctx);
	return ctx;
}