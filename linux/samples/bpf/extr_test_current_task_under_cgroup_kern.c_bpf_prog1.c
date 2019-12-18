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
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  bpf_current_task_under_cgroup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_get_current_pid_tgid () ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_map ; 
 int /*<<< orphan*/  perf_map ; 

int bpf_prog1(struct pt_regs *ctx)
{
	u64 pid = bpf_get_current_pid_tgid();
	int idx = 0;

	if (!bpf_current_task_under_cgroup(&cgroup_map, 0))
		return 0;

	bpf_map_update_elem(&perf_map, &idx, &pid, BPF_ANY);
	return 0;
}