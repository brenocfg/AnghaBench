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
 struct trace_array* graph_array ; 
 int /*<<< orphan*/  smp_mb () ; 

void set_graph_array(struct trace_array *tr)
{
	graph_array = tr;

	/* Make graph_array visible before we start tracing */

	smp_mb();
}