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
struct pt_regs {int dummy; } ;
struct pair {long ip; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  BPF_KRETPROBE_READ_RET_IP (long,struct pt_regs*) ; 
 long PT_REGS_RC (struct pt_regs*) ; 
 int /*<<< orphan*/  bpf_ktime_get_ns () ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,long*,struct pair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_map ; 

int bpf_prog2(struct pt_regs *ctx)
{
	long ptr = PT_REGS_RC(ctx);
	long ip = 0;

	/* get ip address of kmem_cache_alloc_node() caller */
	BPF_KRETPROBE_READ_RET_IP(ip, ctx);

	struct pair v = {
		.val = bpf_ktime_get_ns(),
		.ip = ip,
	};

	bpf_map_update_elem(&my_map, &ptr, &v, BPF_ANY);
	return 0;
}