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
struct task_struct {int dummy; } ;
struct rseq_cs {scalar_t__ abort_ip; int /*<<< orphan*/  post_commit_offset; int /*<<< orphan*/  start_ip; int /*<<< orphan*/  flags; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int clear_rseq_cs (struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_rseq_cs (unsigned long,struct rseq_cs*) ; 
 unsigned long instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  instruction_pointer_set (struct pt_regs*,unsigned long) ; 
 int rseq_get_rseq_cs (struct task_struct*,struct rseq_cs*) ; 
 int rseq_need_restart (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rseq_ip_fixup (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rseq_ip_fixup(struct pt_regs *regs)
{
	unsigned long ip = instruction_pointer(regs);
	struct task_struct *t = current;
	struct rseq_cs rseq_cs;
	int ret;

	ret = rseq_get_rseq_cs(t, &rseq_cs);
	if (ret)
		return ret;

	/*
	 * Handle potentially not being within a critical section.
	 * If not nested over a rseq critical section, restart is useless.
	 * Clear the rseq_cs pointer and return.
	 */
	if (!in_rseq_cs(ip, &rseq_cs))
		return clear_rseq_cs(t);
	ret = rseq_need_restart(t, rseq_cs.flags);
	if (ret <= 0)
		return ret;
	ret = clear_rseq_cs(t);
	if (ret)
		return ret;
	trace_rseq_ip_fixup(ip, rseq_cs.start_ip, rseq_cs.post_commit_offset,
			    rseq_cs.abort_ip);
	instruction_pointer_set(regs, (unsigned long)rseq_cs.abort_ip);
	return 0;
}