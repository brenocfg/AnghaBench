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
 long PT_REGS_PARM1 (struct pt_regs*) ; 
 int /*<<< orphan*/  bpf_ktime_get_ns () ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_map ; 

int bpf_prog1(struct pt_regs *ctx)
{
	long rq = PT_REGS_PARM1(ctx);
	u64 val = bpf_ktime_get_ns();

	bpf_map_update_elem(&my_map, &rq, &val, BPF_ANY);
	return 0;
}