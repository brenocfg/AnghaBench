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
struct thread {int dummy; } ;
struct regs_dump {int /*<<< orphan*/  mask; int /*<<< orphan*/ * regs; int /*<<< orphan*/  abi; } ;
struct perf_sample {struct regs_dump user_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_REGS_MASK ; 
 int PERF_REGS_MAX ; 
 int /*<<< orphan*/  PERF_SAMPLE_REGS_ABI ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  perf_regs_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int sample_ustack (struct perf_sample*,struct thread*,int /*<<< orphan*/ *) ; 

int test__arch_unwind_sample(struct perf_sample *sample,
		struct thread *thread)
{
	struct regs_dump *regs = &sample->user_regs;
	u64 *buf;

	buf = calloc(1, sizeof(u64) * PERF_REGS_MAX);
	if (!buf) {
		pr_debug("failed to allocate sample uregs data\n");
		return -1;
	}

	perf_regs_load(buf);
	regs->abi  = PERF_SAMPLE_REGS_ABI;
	regs->regs = buf;
	regs->mask = PERF_REGS_MASK;

	return sample_ustack(sample, thread, buf);
}