#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;
struct xdp_mem_allocator {int /*<<< orphan*/  rcu; int /*<<< orphan*/  node; int /*<<< orphan*/  page_pool; TYPE_1__ mem; int /*<<< orphan*/  disconnect_cnt; } ;

/* Variables and functions */
 scalar_t__ MEM_TYPE_PAGE_POOL ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  __xdp_mem_allocator_rcu_free ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_id_ht ; 
 int /*<<< orphan*/  mem_id_lock ; 
 int /*<<< orphan*/  mem_id_rht_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int page_pool_request_shutdown (int /*<<< orphan*/ ) ; 
 struct xdp_mem_allocator* rhashtable_lookup_fast (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mem_disconnect (struct xdp_mem_allocator*,int,int) ; 

__attribute__((used)) static bool __mem_id_disconnect(int id, bool force)
{
	struct xdp_mem_allocator *xa;
	bool safe_to_remove = true;

	mutex_lock(&mem_id_lock);

	xa = rhashtable_lookup_fast(mem_id_ht, &id, mem_id_rht_params);
	if (!xa) {
		mutex_unlock(&mem_id_lock);
		WARN(1, "Request remove non-existing id(%d), driver bug?", id);
		return true;
	}
	xa->disconnect_cnt++;

	/* Detects in-flight packet-pages for page_pool */
	if (xa->mem.type == MEM_TYPE_PAGE_POOL)
		safe_to_remove = page_pool_request_shutdown(xa->page_pool);

	trace_mem_disconnect(xa, safe_to_remove, force);

	if ((safe_to_remove || force) &&
	    !rhashtable_remove_fast(mem_id_ht, &xa->node, mem_id_rht_params))
		call_rcu(&xa->rcu, __xdp_mem_allocator_rcu_free);

	mutex_unlock(&mem_id_lock);
	return (safe_to_remove|force);
}