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
#define  BPF_FUNC_strtol 133 
#define  BPF_FUNC_strtoul 132 
#define  BPF_FUNC_sysctl_get_current_value 131 
#define  BPF_FUNC_sysctl_get_name 130 
#define  BPF_FUNC_sysctl_get_new_value 129 
#define  BPF_FUNC_sysctl_set_new_value 128 
 struct bpf_func_proto const bpf_strtol_proto ; 
 struct bpf_func_proto const bpf_strtoul_proto ; 
 struct bpf_func_proto const bpf_sysctl_get_current_value_proto ; 
 struct bpf_func_proto const bpf_sysctl_get_name_proto ; 
 struct bpf_func_proto const bpf_sysctl_get_new_value_proto ; 
 struct bpf_func_proto const bpf_sysctl_set_new_value_proto ; 
 struct bpf_func_proto const* cgroup_base_func_proto (int,struct bpf_prog const*) ; 

__attribute__((used)) static const struct bpf_func_proto *
sysctl_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_strtol:
		return &bpf_strtol_proto;
	case BPF_FUNC_strtoul:
		return &bpf_strtoul_proto;
	case BPF_FUNC_sysctl_get_name:
		return &bpf_sysctl_get_name_proto;
	case BPF_FUNC_sysctl_get_current_value:
		return &bpf_sysctl_get_current_value_proto;
	case BPF_FUNC_sysctl_get_new_value:
		return &bpf_sysctl_get_new_value_proto;
	case BPF_FUNC_sysctl_set_new_value:
		return &bpf_sysctl_set_new_value_proto;
	default:
		return cgroup_base_func_proto(func_id, prog);
	}
}