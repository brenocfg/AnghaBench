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
struct bpf_lru_node {int cpu; int /*<<< orphan*/  list; scalar_t__ ref; int /*<<< orphan*/  type; } ;
struct bpf_lru_locallist {int dummy; } ;
struct bpf_lru {int hash_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LRU_LOCAL_LIST_T_PENDING ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_pending_list (struct bpf_lru_locallist*) ; 

__attribute__((used)) static void __local_list_add_pending(struct bpf_lru *lru,
				     struct bpf_lru_locallist *loc_l,
				     int cpu,
				     struct bpf_lru_node *node,
				     u32 hash)
{
	*(u32 *)((void *)node + lru->hash_offset) = hash;
	node->cpu = cpu;
	node->type = BPF_LRU_LOCAL_LIST_T_PENDING;
	node->ref = 0;
	list_add(&node->list, local_pending_list(loc_l));
}