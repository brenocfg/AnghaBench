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
struct task_struct {int flags; } ;

/* Variables and functions */
 int CPUTIME_IRQ ; 
 int CPUTIME_SOFTIRQ ; 
 int CPUTIME_SYSTEM ; 
 int PF_VCPU ; 
 int /*<<< orphan*/  account_guest_time (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_system_index_time (struct task_struct*,int /*<<< orphan*/ ,int) ; 
 int hardirq_count () ; 
 scalar_t__ in_serving_softirq () ; 
 int irq_count () ; 

void account_system_time(struct task_struct *p, int hardirq_offset, u64 cputime)
{
	int index;

	if ((p->flags & PF_VCPU) && (irq_count() - hardirq_offset == 0)) {
		account_guest_time(p, cputime);
		return;
	}

	if (hardirq_count() - hardirq_offset)
		index = CPUTIME_IRQ;
	else if (in_serving_softirq())
		index = CPUTIME_SOFTIRQ;
	else
		index = CPUTIME_SYSTEM;

	account_system_index_time(p, cputime, index);
}