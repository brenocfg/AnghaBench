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
struct work_struct {int dummy; } ;
struct memory_failure_entry {int flags; int /*<<< orphan*/  pfn; int /*<<< orphan*/  member_0; } ;
struct memory_failure_cpu {int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int MF_SOFT_OFFLINE ; 
 int kfifo_get (int /*<<< orphan*/ *,struct memory_failure_entry*) ; 
 int /*<<< orphan*/  memory_failure (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memory_failure_cpu ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_offline_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct memory_failure_cpu* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void memory_failure_work_func(struct work_struct *work)
{
	struct memory_failure_cpu *mf_cpu;
	struct memory_failure_entry entry = { 0, };
	unsigned long proc_flags;
	int gotten;

	mf_cpu = this_cpu_ptr(&memory_failure_cpu);
	for (;;) {
		spin_lock_irqsave(&mf_cpu->lock, proc_flags);
		gotten = kfifo_get(&mf_cpu->fifo, &entry);
		spin_unlock_irqrestore(&mf_cpu->lock, proc_flags);
		if (!gotten)
			break;
		if (entry.flags & MF_SOFT_OFFLINE)
			soft_offline_page(pfn_to_page(entry.pfn), entry.flags);
		else
			memory_failure(entry.pfn, entry.flags);
	}
}