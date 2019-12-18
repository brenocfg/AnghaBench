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
struct thread {int dummy; } ;
struct perf_sample {int insn_len; int /*<<< orphan*/  insn; int /*<<< orphan*/  ip; } ;
struct machine {int dummy; } ;
struct insn {int length; } ;

/* Variables and functions */
 scalar_t__ insn_complete (struct insn*) ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 int /*<<< orphan*/  insn_init (struct insn*,int /*<<< orphan*/ ,int,int) ; 
 int thread__memcpy (struct thread*,struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

void arch_fetch_insn(struct perf_sample *sample,
		     struct thread *thread,
		     struct machine *machine)
{
	struct insn insn;
	int len;
	bool is64bit = false;

	if (!sample->ip)
		return;
	len = thread__memcpy(thread, machine, sample->insn, sample->ip, sizeof(sample->insn), &is64bit);
	if (len <= 0)
		return;
	insn_init(&insn, sample->insn, len, is64bit);
	insn_get_length(&insn);
	if (insn_complete(&insn) && insn.length <= len)
		sample->insn_len = insn.length;
}