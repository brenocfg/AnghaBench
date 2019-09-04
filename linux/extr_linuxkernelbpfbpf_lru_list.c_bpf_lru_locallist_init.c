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
struct bpf_lru_locallist {int next_steal; int /*<<< orphan*/  lock; int /*<<< orphan*/ * lists; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NR_BPF_LRU_LOCAL_LIST_T ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpf_lru_locallist_init(struct bpf_lru_locallist *loc_l, int cpu)
{
	int i;

	for (i = 0; i < NR_BPF_LRU_LOCAL_LIST_T; i++)
		INIT_LIST_HEAD(&loc_l->lists[i]);

	loc_l->next_steal = cpu;

	raw_spin_lock_init(&loc_l->lock);
}