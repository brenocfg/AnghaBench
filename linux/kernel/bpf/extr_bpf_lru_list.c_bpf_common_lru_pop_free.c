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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_lru_node {int dummy; } ;
struct bpf_lru_locallist {int next_steal; int /*<<< orphan*/  lock; } ;
struct bpf_common_lru {int /*<<< orphan*/  local_list; } ;
struct bpf_lru {struct bpf_common_lru common_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  __local_list_add_pending (struct bpf_lru*,struct bpf_lru_locallist*,int,struct bpf_lru_node*,int /*<<< orphan*/ ) ; 
 struct bpf_lru_node* __local_list_pop_free (struct bpf_lru_locallist*) ; 
 struct bpf_lru_node* __local_list_pop_pending (struct bpf_lru*,struct bpf_lru_locallist*) ; 
 int /*<<< orphan*/  bpf_lru_list_pop_free_to_local (struct bpf_lru*,struct bpf_lru_locallist*) ; 
 int get_next_cpu (int) ; 
 struct bpf_lru_locallist* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct bpf_lru_node *bpf_common_lru_pop_free(struct bpf_lru *lru,
						    u32 hash)
{
	struct bpf_lru_locallist *loc_l, *steal_loc_l;
	struct bpf_common_lru *clru = &lru->common_lru;
	struct bpf_lru_node *node;
	int steal, first_steal;
	unsigned long flags;
	int cpu = raw_smp_processor_id();

	loc_l = per_cpu_ptr(clru->local_list, cpu);

	raw_spin_lock_irqsave(&loc_l->lock, flags);

	node = __local_list_pop_free(loc_l);
	if (!node) {
		bpf_lru_list_pop_free_to_local(lru, loc_l);
		node = __local_list_pop_free(loc_l);
	}

	if (node)
		__local_list_add_pending(lru, loc_l, cpu, node, hash);

	raw_spin_unlock_irqrestore(&loc_l->lock, flags);

	if (node)
		return node;

	/* No free nodes found from the local free list and
	 * the global LRU list.
	 *
	 * Steal from the local free/pending list of the
	 * current CPU and remote CPU in RR.  It starts
	 * with the loc_l->next_steal CPU.
	 */

	first_steal = loc_l->next_steal;
	steal = first_steal;
	do {
		steal_loc_l = per_cpu_ptr(clru->local_list, steal);

		raw_spin_lock_irqsave(&steal_loc_l->lock, flags);

		node = __local_list_pop_free(steal_loc_l);
		if (!node)
			node = __local_list_pop_pending(lru, steal_loc_l);

		raw_spin_unlock_irqrestore(&steal_loc_l->lock, flags);

		steal = get_next_cpu(steal);
	} while (!node && steal != first_steal);

	loc_l->next_steal = steal;

	if (node) {
		raw_spin_lock_irqsave(&loc_l->lock, flags);
		__local_list_add_pending(lru, loc_l, cpu, node, hash);
		raw_spin_unlock_irqrestore(&loc_l->lock, flags);
	}

	return node;
}