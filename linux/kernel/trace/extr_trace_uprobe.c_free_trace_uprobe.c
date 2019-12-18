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
struct trace_uprobe {struct trace_uprobe* filename; int /*<<< orphan*/  tp; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct trace_uprobe*) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_probe_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_trace_uprobe(struct trace_uprobe *tu)
{
	if (!tu)
		return;

	path_put(&tu->path);
	trace_probe_cleanup(&tu->tp);
	kfree(tu->filename);
	kfree(tu);
}