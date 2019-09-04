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
struct TYPE_2__ {int id; } ;
struct xdp_rxq_info {TYPE_1__ mem; } ;
struct xdp_mem_allocator {int /*<<< orphan*/  rcu; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xdp_mem_allocator_rcu_free ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_id_ht ; 
 int /*<<< orphan*/  mem_id_lock ; 
 int /*<<< orphan*/  mem_id_rht_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct xdp_mem_allocator* rhashtable_lookup_fast (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __xdp_rxq_info_unreg_mem_model(struct xdp_rxq_info *xdp_rxq)
{
	struct xdp_mem_allocator *xa;
	int id = xdp_rxq->mem.id;

	if (id == 0)
		return;

	mutex_lock(&mem_id_lock);

	xa = rhashtable_lookup_fast(mem_id_ht, &id, mem_id_rht_params);
	if (xa && !rhashtable_remove_fast(mem_id_ht, &xa->node, mem_id_rht_params))
		call_rcu(&xa->rcu, __xdp_mem_allocator_rcu_free);

	mutex_unlock(&mem_id_lock);
}