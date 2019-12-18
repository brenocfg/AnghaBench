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
struct bpf_prog {int dummy; } ;
struct bpf_func_proto {int dummy; } ;
typedef  enum bpf_func_id { ____Placeholder_bpf_func_id } bpf_func_id ;

/* Variables and functions */
#define  BPF_FUNC_current_task_under_cgroup 150 
#define  BPF_FUNC_get_current_cgroup_id 149 
#define  BPF_FUNC_get_current_comm 148 
#define  BPF_FUNC_get_current_pid_tgid 147 
#define  BPF_FUNC_get_current_task 146 
#define  BPF_FUNC_get_current_uid_gid 145 
#define  BPF_FUNC_get_numa_node_id 144 
#define  BPF_FUNC_get_prandom_u32 143 
#define  BPF_FUNC_get_smp_processor_id 142 
#define  BPF_FUNC_ktime_get_ns 141 
#define  BPF_FUNC_map_delete_elem 140 
#define  BPF_FUNC_map_lookup_elem 139 
#define  BPF_FUNC_map_peek_elem 138 
#define  BPF_FUNC_map_pop_elem 137 
#define  BPF_FUNC_map_push_elem 136 
#define  BPF_FUNC_map_update_elem 135 
#define  BPF_FUNC_perf_event_read 134 
#define  BPF_FUNC_probe_read 133 
#define  BPF_FUNC_probe_read_str 132 
#define  BPF_FUNC_probe_write_user 131 
#define  BPF_FUNC_send_signal 130 
#define  BPF_FUNC_tail_call 129 
#define  BPF_FUNC_trace_printk 128 
 struct bpf_func_proto const bpf_current_task_under_cgroup_proto ; 
 struct bpf_func_proto const bpf_get_current_cgroup_id_proto ; 
 struct bpf_func_proto const bpf_get_current_comm_proto ; 
 struct bpf_func_proto const bpf_get_current_pid_tgid_proto ; 
 struct bpf_func_proto const bpf_get_current_task_proto ; 
 struct bpf_func_proto const bpf_get_current_uid_gid_proto ; 
 struct bpf_func_proto const bpf_get_numa_node_id_proto ; 
 struct bpf_func_proto const bpf_get_prandom_u32_proto ; 
 struct bpf_func_proto const* bpf_get_probe_write_proto () ; 
 struct bpf_func_proto const bpf_get_smp_processor_id_proto ; 
 struct bpf_func_proto const* bpf_get_trace_printk_proto () ; 
 struct bpf_func_proto const bpf_ktime_get_ns_proto ; 
 struct bpf_func_proto const bpf_map_delete_elem_proto ; 
 struct bpf_func_proto const bpf_map_lookup_elem_proto ; 
 struct bpf_func_proto const bpf_map_peek_elem_proto ; 
 struct bpf_func_proto const bpf_map_pop_elem_proto ; 
 struct bpf_func_proto const bpf_map_push_elem_proto ; 
 struct bpf_func_proto const bpf_map_update_elem_proto ; 
 struct bpf_func_proto const bpf_perf_event_read_proto ; 
 struct bpf_func_proto const bpf_probe_read_proto ; 
 struct bpf_func_proto const bpf_probe_read_str_proto ; 
 struct bpf_func_proto const bpf_send_signal_proto ; 
 struct bpf_func_proto const bpf_tail_call_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
tracing_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_map_lookup_elem:
		return &bpf_map_lookup_elem_proto;
	case BPF_FUNC_map_update_elem:
		return &bpf_map_update_elem_proto;
	case BPF_FUNC_map_delete_elem:
		return &bpf_map_delete_elem_proto;
	case BPF_FUNC_map_push_elem:
		return &bpf_map_push_elem_proto;
	case BPF_FUNC_map_pop_elem:
		return &bpf_map_pop_elem_proto;
	case BPF_FUNC_map_peek_elem:
		return &bpf_map_peek_elem_proto;
	case BPF_FUNC_probe_read:
		return &bpf_probe_read_proto;
	case BPF_FUNC_ktime_get_ns:
		return &bpf_ktime_get_ns_proto;
	case BPF_FUNC_tail_call:
		return &bpf_tail_call_proto;
	case BPF_FUNC_get_current_pid_tgid:
		return &bpf_get_current_pid_tgid_proto;
	case BPF_FUNC_get_current_task:
		return &bpf_get_current_task_proto;
	case BPF_FUNC_get_current_uid_gid:
		return &bpf_get_current_uid_gid_proto;
	case BPF_FUNC_get_current_comm:
		return &bpf_get_current_comm_proto;
	case BPF_FUNC_trace_printk:
		return bpf_get_trace_printk_proto();
	case BPF_FUNC_get_smp_processor_id:
		return &bpf_get_smp_processor_id_proto;
	case BPF_FUNC_get_numa_node_id:
		return &bpf_get_numa_node_id_proto;
	case BPF_FUNC_perf_event_read:
		return &bpf_perf_event_read_proto;
	case BPF_FUNC_probe_write_user:
		return bpf_get_probe_write_proto();
	case BPF_FUNC_current_task_under_cgroup:
		return &bpf_current_task_under_cgroup_proto;
	case BPF_FUNC_get_prandom_u32:
		return &bpf_get_prandom_u32_proto;
	case BPF_FUNC_probe_read_str:
		return &bpf_probe_read_str_proto;
#ifdef CONFIG_CGROUPS
	case BPF_FUNC_get_current_cgroup_id:
		return &bpf_get_current_cgroup_id_proto;
#endif
	case BPF_FUNC_send_signal:
		return &bpf_send_signal_proto;
	default:
		return NULL;
	}
}