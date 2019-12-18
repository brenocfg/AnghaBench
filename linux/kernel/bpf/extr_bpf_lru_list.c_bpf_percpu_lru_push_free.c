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
struct bpf_lru_node {int /*<<< orphan*/  cpu; } ;
struct bpf_lru_list {int /*<<< orphan*/  lock; } ;
struct bpf_lru {int /*<<< orphan*/  percpu_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LRU_LIST_T_FREE ; 
 int /*<<< orphan*/  __bpf_lru_node_move (struct bpf_lru_list*,struct bpf_lru_node*,int /*<<< orphan*/ ) ; 
 struct bpf_lru_list* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bpf_percpu_lru_push_free(struct bpf_lru *lru,
				     struct bpf_lru_node *node)
{
	struct bpf_lru_list *l;
	unsigned long flags;

	l = per_cpu_ptr(lru->percpu_lru, node->cpu);

	raw_spin_lock_irqsave(&l->lock, flags);

	__bpf_lru_node_move(l, node, BPF_LRU_LIST_T_FREE);

	raw_spin_unlock_irqrestore(&l->lock, flags);
}