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
struct workqueue_struct {int dummy; } ;
struct workqueue_attrs {int dummy; } ;
struct worker_pool {int /*<<< orphan*/  node; } ;
struct pool_workqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct worker_pool* get_unbound_pool (struct workqueue_attrs const*) ; 
 int /*<<< orphan*/  init_pwq (struct pool_workqueue*,struct workqueue_struct*,struct worker_pool*) ; 
 struct pool_workqueue* kmem_cache_alloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unbound_pool (struct worker_pool*) ; 
 int /*<<< orphan*/  pwq_cache ; 
 int /*<<< orphan*/  wq_pool_mutex ; 

__attribute__((used)) static struct pool_workqueue *alloc_unbound_pwq(struct workqueue_struct *wq,
					const struct workqueue_attrs *attrs)
{
	struct worker_pool *pool;
	struct pool_workqueue *pwq;

	lockdep_assert_held(&wq_pool_mutex);

	pool = get_unbound_pool(attrs);
	if (!pool)
		return NULL;

	pwq = kmem_cache_alloc_node(pwq_cache, GFP_KERNEL, pool->node);
	if (!pwq) {
		put_unbound_pool(pool);
		return NULL;
	}

	init_pwq(pwq, wq, pool);
	return pwq;
}