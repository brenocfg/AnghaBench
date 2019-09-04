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
struct irq_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_printk (char*,...) ; 
 int /*<<< orphan*/  trace_printk_test_global_str_fmt ; 
 int /*<<< orphan*/  trace_printk_test_global_str_irq ; 

__attribute__((used)) static void trace_printk_irq_work(struct irq_work *work)
{
	trace_printk("(irq) This is a static string that will use trace_bputs\n");
	trace_printk(trace_printk_test_global_str_irq);

	trace_printk("(irq) This is a %s that will use trace_bprintk()\n",
		     "static string");

	trace_printk(trace_printk_test_global_str_fmt,
		     "(irq) ", "dynamic string");
}