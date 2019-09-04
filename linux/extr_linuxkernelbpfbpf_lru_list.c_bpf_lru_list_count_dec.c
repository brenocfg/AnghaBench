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
struct bpf_lru_list {int /*<<< orphan*/ * counts; } ;
typedef  enum bpf_lru_list_type { ____Placeholder_bpf_lru_list_type } bpf_lru_list_type ;

/* Variables and functions */
 int NR_BPF_LRU_LIST_COUNT ; 

__attribute__((used)) static void bpf_lru_list_count_dec(struct bpf_lru_list *l,
				   enum bpf_lru_list_type type)
{
	if (type < NR_BPF_LRU_LIST_COUNT)
		l->counts[type]--;
}