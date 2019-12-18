#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ retprobe; } ;
struct perf_probe_event {int nargs; TYPE_1__ point; TYPE_2__* args; } ;
struct perf_probe_arg {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 int MAX_PROBE_ARGS ; 
 int /*<<< orphan*/  argv_free (char**) ; 
 char** argv_split (char const*,int*) ; 
 scalar_t__ is_c_varname (int /*<<< orphan*/ ) ; 
 int parse_perf_probe_arg (char*,TYPE_2__*) ; 
 int parse_perf_probe_point (char*,struct perf_probe_event*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  semantic_error (char*,...) ; 
 TYPE_2__* zalloc (int) ; 

int parse_perf_probe_command(const char *cmd, struct perf_probe_event *pev)
{
	char **argv;
	int argc, i, ret = 0;

	argv = argv_split(cmd, &argc);
	if (!argv) {
		pr_debug("Failed to split arguments.\n");
		return -ENOMEM;
	}
	if (argc - 1 > MAX_PROBE_ARGS) {
		semantic_error("Too many probe arguments (%d).\n", argc - 1);
		ret = -ERANGE;
		goto out;
	}
	/* Parse probe point */
	ret = parse_perf_probe_point(argv[0], pev);
	if (ret < 0)
		goto out;

	/* Copy arguments and ensure return probe has no C argument */
	pev->nargs = argc - 1;
	pev->args = zalloc(sizeof(struct perf_probe_arg) * pev->nargs);
	if (pev->args == NULL) {
		ret = -ENOMEM;
		goto out;
	}
	for (i = 0; i < pev->nargs && ret >= 0; i++) {
		ret = parse_perf_probe_arg(argv[i + 1], &pev->args[i]);
		if (ret >= 0 &&
		    is_c_varname(pev->args[i].var) && pev->point.retprobe) {
			semantic_error("You can't specify local variable for"
				       " kretprobe.\n");
			ret = -EINVAL;
		}
	}
out:
	argv_free(argv);

	return ret;
}