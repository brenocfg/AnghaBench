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
struct trace_uprobe {int /*<<< orphan*/  tp; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct trace_uprobe* to_trace_uprobe (struct dyn_event*) ; 
 int /*<<< orphan*/  trace_probe_group_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_probe_name (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_uprobe_match_command_head (struct trace_uprobe*,int,char const**) ; 

__attribute__((used)) static bool trace_uprobe_match(const char *system, const char *event,
			int argc, const char **argv, struct dyn_event *ev)
{
	struct trace_uprobe *tu = to_trace_uprobe(ev);

	return strcmp(trace_probe_name(&tu->tp), event) == 0 &&
	   (!system || strcmp(trace_probe_group_name(&tu->tp), system) == 0) &&
	   trace_uprobe_match_command_head(tu, argc, argv);
}