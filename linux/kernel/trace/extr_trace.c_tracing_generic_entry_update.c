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
struct trace_entry {int preempt_count; unsigned short type; int flags; int /*<<< orphan*/  pid; } ;
struct task_struct {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int HARDIRQ_MASK ; 
 int NMI_MASK ; 
 int SOFTIRQ_OFFSET ; 
 int TRACE_FLAG_HARDIRQ ; 
 int TRACE_FLAG_IRQS_NOSUPPORT ; 
 int TRACE_FLAG_IRQS_OFF ; 
 int TRACE_FLAG_NEED_RESCHED ; 
 int TRACE_FLAG_NMI ; 
 int TRACE_FLAG_PREEMPT_RESCHED ; 
 int TRACE_FLAG_SOFTIRQ ; 
 struct task_struct* current ; 
 scalar_t__ irqs_disabled_flags (unsigned long) ; 
 scalar_t__ test_preempt_need_resched () ; 
 scalar_t__ tif_need_resched () ; 

void
tracing_generic_entry_update(struct trace_entry *entry, unsigned short type,
			     unsigned long flags, int pc)
{
	struct task_struct *tsk = current;

	entry->preempt_count		= pc & 0xff;
	entry->pid			= (tsk) ? tsk->pid : 0;
	entry->type			= type;
	entry->flags =
#ifdef CONFIG_TRACE_IRQFLAGS_SUPPORT
		(irqs_disabled_flags(flags) ? TRACE_FLAG_IRQS_OFF : 0) |
#else
		TRACE_FLAG_IRQS_NOSUPPORT |
#endif
		((pc & NMI_MASK    ) ? TRACE_FLAG_NMI     : 0) |
		((pc & HARDIRQ_MASK) ? TRACE_FLAG_HARDIRQ : 0) |
		((pc & SOFTIRQ_OFFSET) ? TRACE_FLAG_SOFTIRQ : 0) |
		(tif_need_resched() ? TRACE_FLAG_NEED_RESCHED : 0) |
		(test_preempt_need_resched() ? TRACE_FLAG_PREEMPT_RESCHED : 0);
}