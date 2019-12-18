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
struct TYPE_2__ {int /*<<< orphan*/  map; } ;
struct trace {TYPE_1__ filter_pids; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace__find_bpf_map_by_name (struct trace*,char*) ; 

__attribute__((used)) static void trace__set_bpf_map_filtered_pids(struct trace *trace)
{
	trace->filter_pids.map = trace__find_bpf_map_by_name(trace, "pids_filtered");
}