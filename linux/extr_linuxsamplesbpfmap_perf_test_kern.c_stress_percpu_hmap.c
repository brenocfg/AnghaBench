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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  bpf_get_current_pid_tgid () ; 
 int /*<<< orphan*/  bpf_map_delete_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_hash_map ; 

int stress_percpu_hmap(struct pt_regs *ctx)
{
	u32 key = bpf_get_current_pid_tgid();
	long init_val = 1;
	long *value;

	bpf_map_update_elem(&percpu_hash_map, &key, &init_val, BPF_ANY);
	value = bpf_map_lookup_elem(&percpu_hash_map, &key);
	if (value)
		bpf_map_delete_elem(&percpu_hash_map, &key);
	return 0;
}