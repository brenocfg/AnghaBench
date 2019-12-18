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
typedef  size_t u32 ;
struct bpf_cpu_map_entry {int /*<<< orphan*/  kthread_stop_wq; int /*<<< orphan*/  rcu; } ;
struct bpf_cpu_map {int /*<<< orphan*/ * cpu_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cpu_map_entry_free ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_map_kthread_stop ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct bpf_cpu_map_entry* xchg (int /*<<< orphan*/ *,struct bpf_cpu_map_entry*) ; 

__attribute__((used)) static void __cpu_map_entry_replace(struct bpf_cpu_map *cmap,
				    u32 key_cpu, struct bpf_cpu_map_entry *rcpu)
{
	struct bpf_cpu_map_entry *old_rcpu;

	old_rcpu = xchg(&cmap->cpu_map[key_cpu], rcpu);
	if (old_rcpu) {
		call_rcu(&old_rcpu->rcu, __cpu_map_entry_free);
		INIT_WORK(&old_rcpu->kthread_stop_wq, cpu_map_kthread_stop);
		schedule_work(&old_rcpu->kthread_stop_wq);
	}
}