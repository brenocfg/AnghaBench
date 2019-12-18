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
struct pt_regs {int dummy; } ;
struct kprobe {scalar_t__ (* fault_handler ) (struct kprobe*,struct pt_regs*,int) ;} ;

/* Variables and functions */
 struct kprobe* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprobe_instance ; 
 scalar_t__ stub1 (struct kprobe*,struct pt_regs*,int) ; 

__attribute__((used)) static int aggr_fault_handler(struct kprobe *p, struct pt_regs *regs,
			      int trapnr)
{
	struct kprobe *cur = __this_cpu_read(kprobe_instance);

	/*
	 * if we faulted "during" the execution of a user specified
	 * probe handler, invoke just that probe's fault handler
	 */
	if (cur && cur->fault_handler) {
		if (cur->fault_handler(cur, regs, trapnr))
			return 1;
	}
	return 0;
}