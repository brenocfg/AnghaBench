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
struct probe_trace_event {int nargs; TYPE_1__* args; int /*<<< orphan*/  uprobes; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strglobmatch (int /*<<< orphan*/ ,char*) ; 
 char* synthesize_probe_trace_command (struct probe_trace_event*) ; 

__attribute__((used)) static void warn_uprobe_event_compat(struct probe_trace_event *tev)
{
	int i;
	char *buf = synthesize_probe_trace_command(tev);

	/* Old uprobe event doesn't support memory dereference */
	if (!tev->uprobes || tev->nargs == 0 || !buf)
		goto out;

	for (i = 0; i < tev->nargs; i++)
		if (strglobmatch(tev->args[i].value, "[$@+-]*")) {
			pr_warning("Please upgrade your kernel to at least "
				   "3.14 to have access to feature %s\n",
				   tev->args[i].value);
			break;
		}
out:
	free(buf);
}