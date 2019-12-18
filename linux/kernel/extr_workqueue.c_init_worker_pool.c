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
struct worker_pool {int id; int cpu; int refcnt; int /*<<< orphan*/  attrs; int /*<<< orphan*/  hash_node; int /*<<< orphan*/  worker_ida; int /*<<< orphan*/  workers; int /*<<< orphan*/  mayday_timer; int /*<<< orphan*/  idle_timer; int /*<<< orphan*/  busy_hash; int /*<<< orphan*/  idle_list; int /*<<< orphan*/  worklist; int /*<<< orphan*/  watchdog_ts; int /*<<< orphan*/  flags; int /*<<< orphan*/  node; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  POOL_DISASSOCIATED ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 int /*<<< orphan*/  alloc_workqueue_attrs () ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_worker_timeout ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pool_mayday_timeout ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_worker_pool(struct worker_pool *pool)
{
	spin_lock_init(&pool->lock);
	pool->id = -1;
	pool->cpu = -1;
	pool->node = NUMA_NO_NODE;
	pool->flags |= POOL_DISASSOCIATED;
	pool->watchdog_ts = jiffies;
	INIT_LIST_HEAD(&pool->worklist);
	INIT_LIST_HEAD(&pool->idle_list);
	hash_init(pool->busy_hash);

	timer_setup(&pool->idle_timer, idle_worker_timeout, TIMER_DEFERRABLE);

	timer_setup(&pool->mayday_timer, pool_mayday_timeout, 0);

	INIT_LIST_HEAD(&pool->workers);

	ida_init(&pool->worker_ida);
	INIT_HLIST_NODE(&pool->hash_node);
	pool->refcnt = 1;

	/* shouldn't fail above this point */
	pool->attrs = alloc_workqueue_attrs();
	if (!pool->attrs)
		return -ENOMEM;
	return 0;
}