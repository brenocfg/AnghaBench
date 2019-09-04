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
struct bpf_lru_node {scalar_t__ type; int /*<<< orphan*/  list; scalar_t__ ref; int /*<<< orphan*/  cpu; } ;
struct bpf_lru_locallist {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lru_list; int /*<<< orphan*/  local_list; } ;
struct bpf_lru {TYPE_1__ common_lru; } ;

/* Variables and functions */
 scalar_t__ BPF_LRU_LIST_T_FREE ; 
 scalar_t__ BPF_LRU_LOCAL_LIST_T_FREE ; 
 scalar_t__ BPF_LRU_LOCAL_LIST_T_PENDING ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bpf_lru_list_push_free (int /*<<< orphan*/ *,struct bpf_lru_node*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_free_list (struct bpf_lru_locallist*) ; 
 struct bpf_lru_locallist* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void bpf_common_lru_push_free(struct bpf_lru *lru,
				     struct bpf_lru_node *node)
{
	unsigned long flags;

	if (WARN_ON_ONCE(node->type == BPF_LRU_LIST_T_FREE) ||
	    WARN_ON_ONCE(node->type == BPF_LRU_LOCAL_LIST_T_FREE))
		return;

	if (node->type == BPF_LRU_LOCAL_LIST_T_PENDING) {
		struct bpf_lru_locallist *loc_l;

		loc_l = per_cpu_ptr(lru->common_lru.local_list, node->cpu);

		raw_spin_lock_irqsave(&loc_l->lock, flags);

		if (unlikely(node->type != BPF_LRU_LOCAL_LIST_T_PENDING)) {
			raw_spin_unlock_irqrestore(&loc_l->lock, flags);
			goto check_lru_list;
		}

		node->type = BPF_LRU_LOCAL_LIST_T_FREE;
		node->ref = 0;
		list_move(&node->list, local_free_list(loc_l));

		raw_spin_unlock_irqrestore(&loc_l->lock, flags);
		return;
	}

check_lru_list:
	bpf_lru_list_push_free(&lru->common_lru.lru_list, node);
}