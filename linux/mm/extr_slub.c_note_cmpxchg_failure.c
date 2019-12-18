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
struct kmem_cache {int /*<<< orphan*/  name; TYPE_1__* cpu_slab; } ;
struct TYPE_2__ {int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPXCHG_DOUBLE_CPU_FAIL ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_tid (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  stat (struct kmem_cache const*,int /*<<< orphan*/ ) ; 
 scalar_t__ tid_to_cpu (unsigned long) ; 
 scalar_t__ tid_to_event (unsigned long) ; 

__attribute__((used)) static inline void note_cmpxchg_failure(const char *n,
		const struct kmem_cache *s, unsigned long tid)
{
#ifdef SLUB_DEBUG_CMPXCHG
	unsigned long actual_tid = __this_cpu_read(s->cpu_slab->tid);

	pr_info("%s %s: cmpxchg redo ", n, s->name);

#ifdef CONFIG_PREEMPT
	if (tid_to_cpu(tid) != tid_to_cpu(actual_tid))
		pr_warn("due to cpu change %d -> %d\n",
			tid_to_cpu(tid), tid_to_cpu(actual_tid));
	else
#endif
	if (tid_to_event(tid) != tid_to_event(actual_tid))
		pr_warn("due to cpu running other code. Event %ld->%ld\n",
			tid_to_event(tid), tid_to_event(actual_tid));
	else
		pr_warn("for unknown reason: actual=%lx was=%lx target=%lx\n",
			actual_tid, tid, next_tid(tid));
#endif
	stat(s, CMPXCHG_DOUBLE_CPU_FAIL);
}