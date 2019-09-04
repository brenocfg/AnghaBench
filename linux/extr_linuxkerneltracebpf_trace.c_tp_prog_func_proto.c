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
#define  BPF_FUNC_get_stack 130 
#define  BPF_FUNC_get_stackid 129 
#define  BPF_FUNC_perf_event_output 128 
 struct bpf_func_proto const bpf_get_stack_proto_tp ; 
 struct bpf_func_proto const bpf_get_stackid_proto_tp ; 
 struct bpf_func_proto const bpf_perf_event_output_proto_tp ; 
 struct bpf_func_proto const* tracing_func_proto (int,struct bpf_prog const*) ; 

__attribute__((used)) static const struct bpf_func_proto *
tp_prog_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_perf_event_output:
		return &bpf_perf_event_output_proto_tp;
	case BPF_FUNC_get_stackid:
		return &bpf_get_stackid_proto_tp;
	case BPF_FUNC_get_stack:
		return &bpf_get_stack_proto_tp;
	default:
		return tracing_func_proto(func_id, prog);
	}
}