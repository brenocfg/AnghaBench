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
typedef  int /*<<< orphan*/  __u64 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_get_current_cgroup_id () ; 
 scalar_t__ bpf_get_current_pid_tgid () ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  cg_ids ; 
 int /*<<< orphan*/  pidmap ; 

int trace(void *ctx)
{
	__u32 pid = bpf_get_current_pid_tgid();
	__u32 key = 0, *expected_pid;
	__u64 *val;

	expected_pid = bpf_map_lookup_elem(&pidmap, &key);
	if (!expected_pid || *expected_pid != pid)
		return 0;

	val = bpf_map_lookup_elem(&cg_ids, &key);
	if (val)
		*val = bpf_get_current_cgroup_id();

	return 0;
}