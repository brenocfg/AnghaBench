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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct task_struct {int dummy; } ;
struct strobelight_bpf_sample {int pid; int ktime; void* user_stack_id; void* kernel_stack_id; int /*<<< orphan*/  metadata; int /*<<< orphan*/  has_meta; int /*<<< orphan*/  comm; } ;
struct pt_regs {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_USER_STACK ; 
 int STACK_TABLE_EPOCH_SHIFT ; 
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 int /*<<< orphan*/  bpf_get_current_comm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bpf_get_current_pid_tgid () ; 
 scalar_t__ bpf_get_current_task () ; 
 void* bpf_get_stackid (struct pt_regs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bpf_ktime_get_ns () ; 
 struct strobelight_bpf_sample* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_perf_event_output (struct pt_regs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct strobelight_bpf_sample*,int) ; 
 void* read_strobe_meta (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sample_heap ; 
 int /*<<< orphan*/  samples ; 
 int /*<<< orphan*/  stacks_0 ; 
 int /*<<< orphan*/  stacks_1 ; 

int on_event(struct pt_regs *ctx) {
	pid_t pid =  bpf_get_current_pid_tgid() >> 32;
	struct strobelight_bpf_sample* sample;
	struct task_struct *task;
	uint32_t zero = 0;
	uint64_t ktime_ns;
	void *sample_end;

	sample = bpf_map_lookup_elem(&sample_heap, &zero);
	if (!sample)
		return 0; /* this will never happen */

	sample->pid = pid;
	bpf_get_current_comm(&sample->comm, TASK_COMM_LEN);
	ktime_ns = bpf_ktime_get_ns();
	sample->ktime = ktime_ns;

	task = (struct task_struct *)bpf_get_current_task();
	sample_end = read_strobe_meta(task, &sample->metadata);
	sample->has_meta = sample_end != NULL;
	sample_end = sample_end ? : &sample->metadata;

	if ((ktime_ns >> STACK_TABLE_EPOCH_SHIFT) & 1) {
		sample->kernel_stack_id = bpf_get_stackid(ctx, &stacks_1, 0);
		sample->user_stack_id = bpf_get_stackid(ctx, &stacks_1, BPF_F_USER_STACK);
	} else {
		sample->kernel_stack_id = bpf_get_stackid(ctx, &stacks_0, 0);
		sample->user_stack_id = bpf_get_stackid(ctx, &stacks_0, BPF_F_USER_STACK);
	}

	uint64_t sample_size = sample_end - (void *)sample;
	/* should always be true */
	if (sample_size < sizeof(struct strobelight_bpf_sample))
		bpf_perf_event_output(ctx, &samples, 0, sample, 1 + sample_size);
	return 0;
}