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
struct augmented_args_payload {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_F_CURRENT_CPU ; 
 int /*<<< orphan*/  __augmented_syscalls__ ; 
 int perf_event_output (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct augmented_args_payload*,int) ; 

__attribute__((used)) static inline int augmented__output(void *ctx, struct augmented_args_payload *args, int len)
{
	/* If perf_event_output fails, return non-zero so that it gets recorded unaugmented */
	return perf_event_output(ctx, &__augmented_syscalls__, BPF_F_CURRENT_CPU, args, len);
}