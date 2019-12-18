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
typedef  int uint64_t ;
struct task_struct {int /*<<< orphan*/  tgid; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int* out; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int*,int /*<<< orphan*/ *) ; 
 int bpf_get_current_pid_tgid () ; 
 scalar_t__ bpf_get_current_task () ; 
 TYPE_1__ data ; 

int test_core_kernel(void *ctx)
{
	struct task_struct *task = (void *)bpf_get_current_task();
	uint64_t pid_tgid = bpf_get_current_pid_tgid();
	int pid, tgid;

	if (BPF_CORE_READ(&pid, &task->pid) ||
	    BPF_CORE_READ(&tgid, &task->tgid))
		return 1;

	/* validate pid + tgid matches */
	data.out[0] = (((uint64_t)pid << 32) | tgid) == pid_tgid;

	return 0;
}