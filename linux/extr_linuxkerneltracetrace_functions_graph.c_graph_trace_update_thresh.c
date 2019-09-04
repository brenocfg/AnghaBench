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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int graph_trace_init (struct trace_array*) ; 
 int /*<<< orphan*/  graph_trace_reset (struct trace_array*) ; 

__attribute__((used)) static int graph_trace_update_thresh(struct trace_array *tr)
{
	graph_trace_reset(tr);
	return graph_trace_init(tr);
}