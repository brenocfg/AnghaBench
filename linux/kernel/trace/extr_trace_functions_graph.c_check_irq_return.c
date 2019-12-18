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
typedef  int u32 ;
struct trace_iterator {int cpu; struct fgraph_data* private; } ;
struct fgraph_data {int /*<<< orphan*/  cpu_data; } ;
struct TYPE_2__ {int depth_irq; } ;

/* Variables and functions */
 int TRACE_GRAPH_PRINT_IRQS ; 
 TYPE_1__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
check_irq_return(struct trace_iterator *iter, u32 flags, int depth)
{
	int cpu = iter->cpu;
	int *depth_irq;
	struct fgraph_data *data = iter->private;

	/*
	 * If we are either displaying irqs, or we got called as
	 * a graph event and private data does not exist,
	 * then we bypass the irq check.
	 */
	if ((flags & TRACE_GRAPH_PRINT_IRQS) ||
	    (!data))
		return 0;

	depth_irq = &(per_cpu_ptr(data->cpu_data, cpu)->depth_irq);

	/*
	 * We are not inside the irq code.
	 */
	if (*depth_irq == -1)
		return 0;

	/*
	 * We are inside the irq code, and this is returning entry.
	 * Let's not trace it and clear the entry depth, since
	 * we are out of irq code.
	 *
	 * This condition ensures that we 'leave the irq code' once
	 * we are out of the entry depth. Thus protecting us from
	 * the RETURN entry loss.
	 */
	if (*depth_irq >= depth) {
		*depth_irq = -1;
		return 1;
	}

	/*
	 * We are inside the irq code, and this is not the entry.
	 */
	return 1;
}