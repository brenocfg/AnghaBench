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
struct perf_ftrace {int graph_depth; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ write_tracing_file (char*,char*) ; 

__attribute__((used)) static int set_tracing_depth(struct perf_ftrace *ftrace)
{
	char buf[16];

	if (ftrace->graph_depth == 0)
		return 0;

	if (ftrace->graph_depth < 0) {
		pr_err("invalid graph depth: %d\n", ftrace->graph_depth);
		return -1;
	}

	snprintf(buf, sizeof(buf), "%d", ftrace->graph_depth);

	if (write_tracing_file("max_graph_depth", buf) < 0)
		return -1;

	return 0;
}