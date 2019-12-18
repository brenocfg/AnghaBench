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
struct syscall {int args_size; } ;
struct perf_sample {int raw_size; void* raw_data; } ;

/* Variables and functions */

__attribute__((used)) static void *syscall__augmented_args(struct syscall *sc, struct perf_sample *sample, int *augmented_args_size, int raw_augmented_args_size)
{
	void *augmented_args = NULL;
	/*
	 * For now with BPF raw_augmented we hook into raw_syscalls:sys_enter
	 * and there we get all 6 syscall args plus the tracepoint common fields
	 * that gets calculated at the start and the syscall_nr (another long).
	 * So we check if that is the case and if so don't look after the
	 * sc->args_size but always after the full raw_syscalls:sys_enter payload,
	 * which is fixed.
	 *
	 * We'll revisit this later to pass s->args_size to the BPF augmenter
	 * (now tools/perf/examples/bpf/augmented_raw_syscalls.c, so that it
	 * copies only what we need for each syscall, like what happens when we
	 * use syscalls:sys_enter_NAME, so that we reduce the kernel/userspace
	 * traffic to just what is needed for each syscall.
	 */
	int args_size = raw_augmented_args_size ?: sc->args_size;

	*augmented_args_size = sample->raw_size - args_size;
	if (*augmented_args_size > 0)
		augmented_args = sample->raw_data + args_size;

	return augmented_args;
}