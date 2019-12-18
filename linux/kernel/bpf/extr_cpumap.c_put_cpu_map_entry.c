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
struct bpf_cpu_map_entry {struct bpf_cpu_map_entry* queue; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cpu_map_ring_cleanup (struct bpf_cpu_map_entry*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bpf_cpu_map_entry*) ; 
 int /*<<< orphan*/  ptr_ring_cleanup (struct bpf_cpu_map_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_cpu_map_entry(struct bpf_cpu_map_entry *rcpu)
{
	if (atomic_dec_and_test(&rcpu->refcnt)) {
		/* The queue should be empty at this point */
		__cpu_map_ring_cleanup(rcpu->queue);
		ptr_ring_cleanup(rcpu->queue, NULL);
		kfree(rcpu->queue);
		kfree(rcpu);
	}
}