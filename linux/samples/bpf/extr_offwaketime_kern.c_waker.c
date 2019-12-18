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
struct wokeby_t {int /*<<< orphan*/  ret; int /*<<< orphan*/  name; } ;
struct task_struct {int /*<<< orphan*/  pid; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 scalar_t__ PT_REGS_PARM1 (struct pt_regs*) ; 
 int /*<<< orphan*/  STACKID_FLAGS ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_get_current_comm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bpf_get_stackid (struct pt_regs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wokeby_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackmap ; 
 int /*<<< orphan*/  wokeby ; 

int waker(struct pt_regs *ctx)
{
	struct task_struct *p = (void *) PT_REGS_PARM1(ctx);
	struct wokeby_t woke;
	u32 pid;

	pid = _(p->pid);

	bpf_get_current_comm(&woke.name, sizeof(woke.name));
	woke.ret = bpf_get_stackid(ctx, &stackmap, STACKID_FLAGS);

	bpf_map_update_elem(&wokeby, &pid, &woke, BPF_ANY);
	return 0;
}