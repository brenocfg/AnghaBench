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
typedef  scalar_t__ u32 ;
struct bpf_lru_node {size_t type; int /*<<< orphan*/  list; scalar_t__ ref; } ;
struct bpf_lru_list {int /*<<< orphan*/ * lists; } ;
struct TYPE_2__ {struct bpf_lru_list lru_list; } ;
struct bpf_lru {TYPE_1__ common_lru; } ;

/* Variables and functions */
 size_t BPF_LRU_LIST_T_FREE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpf_common_lru_populate(struct bpf_lru *lru, void *buf,
				    u32 node_offset, u32 elem_size,
				    u32 nr_elems)
{
	struct bpf_lru_list *l = &lru->common_lru.lru_list;
	u32 i;

	for (i = 0; i < nr_elems; i++) {
		struct bpf_lru_node *node;

		node = (struct bpf_lru_node *)(buf + node_offset);
		node->type = BPF_LRU_LIST_T_FREE;
		node->ref = 0;
		list_add(&node->list, &l->lists[BPF_LRU_LIST_T_FREE]);
		buf += elem_size;
	}
}