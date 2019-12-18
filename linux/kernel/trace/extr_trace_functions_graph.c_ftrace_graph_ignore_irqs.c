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

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IRQ_BIT ; 
 int /*<<< orphan*/  ftrace_graph_skip_irqs ; 
 int in_irq () ; 
 scalar_t__ trace_recursion_test (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ftrace_graph_ignore_irqs(void)
{
	if (!ftrace_graph_skip_irqs || trace_recursion_test(TRACE_IRQ_BIT))
		return 0;

	return in_irq();
}