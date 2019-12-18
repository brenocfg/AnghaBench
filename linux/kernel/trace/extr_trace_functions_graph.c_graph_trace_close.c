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
struct trace_iterator {struct fgraph_data* private; } ;
struct fgraph_data {int /*<<< orphan*/  cpu_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fgraph_data*) ; 

void graph_trace_close(struct trace_iterator *iter)
{
	struct fgraph_data *data = iter->private;

	if (data) {
		free_percpu(data->cpu_data);
		kfree(data);
	}
}