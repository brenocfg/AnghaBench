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
struct z3fold_pool {int /*<<< orphan*/  release_wq; int /*<<< orphan*/  compact_wq; int /*<<< orphan*/  c_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct z3fold_pool*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z3fold_unregister_migration (struct z3fold_pool*) ; 

__attribute__((used)) static void z3fold_destroy_pool(struct z3fold_pool *pool)
{
	kmem_cache_destroy(pool->c_handle);

	/*
	 * We need to destroy pool->compact_wq before pool->release_wq,
	 * as any pending work on pool->compact_wq will call
	 * queue_work(pool->release_wq, &pool->work).
	 *
	 * There are still outstanding pages until both workqueues are drained,
	 * so we cannot unregister migration until then.
	 */

	destroy_workqueue(pool->compact_wq);
	destroy_workqueue(pool->release_wq);
	z3fold_unregister_migration(pool);
	kfree(pool);
}