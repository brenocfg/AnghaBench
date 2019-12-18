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
#define  BPF_FUNC_get_current_cgroup_id 137 
#define  BPF_FUNC_get_current_uid_gid 136 
#define  BPF_FUNC_get_local_storage 135 
#define  BPF_FUNC_map_delete_elem 134 
#define  BPF_FUNC_map_lookup_elem 133 
#define  BPF_FUNC_map_peek_elem 132 
#define  BPF_FUNC_map_pop_elem 131 
#define  BPF_FUNC_map_push_elem 130 
#define  BPF_FUNC_map_update_elem 129 
#define  BPF_FUNC_trace_printk 128 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 struct bpf_func_proto const bpf_get_current_cgroup_id_proto ; 
 struct bpf_func_proto const bpf_get_current_uid_gid_proto ; 
 struct bpf_func_proto const bpf_get_local_storage_proto ; 
 struct bpf_func_proto const* bpf_get_trace_printk_proto () ; 
 struct bpf_func_proto const bpf_map_delete_elem_proto ; 
 struct bpf_func_proto const bpf_map_lookup_elem_proto ; 
 struct bpf_func_proto const bpf_map_peek_elem_proto ; 
 struct bpf_func_proto const bpf_map_pop_elem_proto ; 
 struct bpf_func_proto const bpf_map_push_elem_proto ; 
 struct bpf_func_proto const bpf_map_update_elem_proto ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct bpf_func_proto *
cgroup_base_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
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
	case BPF_FUNC_get_current_uid_gid:
		return &bpf_get_current_uid_gid_proto;
	case BPF_FUNC_get_local_storage:
		return &bpf_get_local_storage_proto;
	case BPF_FUNC_get_current_cgroup_id:
		return &bpf_get_current_cgroup_id_proto;
	case BPF_FUNC_trace_printk:
		if (capable(CAP_SYS_ADMIN))
			return bpf_get_trace_printk_proto();
		/* fall through */
	default:
		return NULL;
	}
}