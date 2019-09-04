#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_env {int seen_direct_write; TYPE_1__* prog; } ;
struct bpf_call_arg_meta {int pkt_access; } ;
typedef  enum bpf_access_type { ____Placeholder_bpf_access_type } bpf_access_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  BPF_PROG_TYPE_LWT_IN 137 
#define  BPF_PROG_TYPE_LWT_OUT 136 
#define  BPF_PROG_TYPE_LWT_SEG6LOCAL 135 
#define  BPF_PROG_TYPE_LWT_XMIT 134 
#define  BPF_PROG_TYPE_SCHED_ACT 133 
#define  BPF_PROG_TYPE_SCHED_CLS 132 
#define  BPF_PROG_TYPE_SK_MSG 131 
#define  BPF_PROG_TYPE_SK_REUSEPORT 130 
#define  BPF_PROG_TYPE_SK_SKB 129 
#define  BPF_PROG_TYPE_XDP 128 
 int BPF_WRITE ; 

__attribute__((used)) static bool may_access_direct_pkt_data(struct bpf_verifier_env *env,
				       const struct bpf_call_arg_meta *meta,
				       enum bpf_access_type t)
{
	switch (env->prog->type) {
	case BPF_PROG_TYPE_LWT_IN:
	case BPF_PROG_TYPE_LWT_OUT:
	case BPF_PROG_TYPE_LWT_SEG6LOCAL:
	case BPF_PROG_TYPE_SK_REUSEPORT:
		/* dst_input() and dst_output() can't write for now */
		if (t == BPF_WRITE)
			return false;
		/* fallthrough */
	case BPF_PROG_TYPE_SCHED_CLS:
	case BPF_PROG_TYPE_SCHED_ACT:
	case BPF_PROG_TYPE_XDP:
	case BPF_PROG_TYPE_LWT_XMIT:
	case BPF_PROG_TYPE_SK_SKB:
	case BPF_PROG_TYPE_SK_MSG:
		if (meta)
			return meta->pkt_access;

		env->seen_direct_write = true;
		return true;
	default:
		return false;
	}
}