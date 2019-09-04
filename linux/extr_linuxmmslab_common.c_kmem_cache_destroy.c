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
struct kmem_cache {int /*<<< orphan*/  name; scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  flush_memcg_workqueue (struct kmem_cache*) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  get_online_mems () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  put_online_mems () ; 
 int shutdown_cache (struct kmem_cache*) ; 
 int shutdown_memcg_caches (struct kmem_cache*) ; 
 int /*<<< orphan*/  slab_mutex ; 
 scalar_t__ unlikely (int) ; 

void kmem_cache_destroy(struct kmem_cache *s)
{
	int err;

	if (unlikely(!s))
		return;

	flush_memcg_workqueue(s);

	get_online_cpus();
	get_online_mems();

	mutex_lock(&slab_mutex);

	s->refcount--;
	if (s->refcount)
		goto out_unlock;

	err = shutdown_memcg_caches(s);
	if (!err)
		err = shutdown_cache(s);

	if (err) {
		pr_err("kmem_cache_destroy %s: Slab cache still has objects\n",
		       s->name);
		dump_stack();
	}
out_unlock:
	mutex_unlock(&slab_mutex);

	put_online_mems();
	put_online_cpus();
}