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
typedef  int /*<<< orphan*/  zend_call_graph ;

/* Variables and functions */

__attribute__((used)) static void zend_sort_op_arrays(zend_call_graph *call_graph)
{
	(void) call_graph;

	// TODO: perform topological sort of cyclic call graph
}