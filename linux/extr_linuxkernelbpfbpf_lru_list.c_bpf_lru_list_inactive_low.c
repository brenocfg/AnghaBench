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
struct bpf_lru_list {scalar_t__* counts; } ;

/* Variables and functions */
 size_t BPF_LRU_LIST_T_ACTIVE ; 
 size_t BPF_LRU_LIST_T_INACTIVE ; 

__attribute__((used)) static bool bpf_lru_list_inactive_low(const struct bpf_lru_list *l)
{
	return l->counts[BPF_LRU_LIST_T_INACTIVE] <
		l->counts[BPF_LRU_LIST_T_ACTIVE];
}