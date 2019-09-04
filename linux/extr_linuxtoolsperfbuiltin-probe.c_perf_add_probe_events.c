#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  module; } ;
struct probe_trace_event {char* group; char* event; TYPE_1__ point; } ;
struct perf_probe_event {int ntevs; struct probe_trace_event* tevs; int /*<<< orphan*/  uprobes; } ;
struct TYPE_4__ {char command; } ;

/* Variables and functions */
 int apply_perf_probe_events (struct perf_probe_event*,int) ; 
 int /*<<< orphan*/  cleanup_perf_probe_events (struct perf_probe_event*,int) ; 
 int convert_perf_probe_events (struct perf_probe_event*,int) ; 
 int /*<<< orphan*/  exit_probe_symbol_maps () ; 
 int init_probe_symbol_maps (int /*<<< orphan*/ ) ; 
 TYPE_2__ params ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  show_perf_probe_event (char*,char*,struct perf_probe_event*,int /*<<< orphan*/ ,int) ; 
 int show_probe_trace_events (struct perf_probe_event*,int) ; 

__attribute__((used)) static int perf_add_probe_events(struct perf_probe_event *pevs, int npevs)
{
	int ret;
	int i, k;
	const char *event = NULL, *group = NULL;

	ret = init_probe_symbol_maps(pevs->uprobes);
	if (ret < 0)
		return ret;

	ret = convert_perf_probe_events(pevs, npevs);
	if (ret < 0)
		goto out_cleanup;

	if (params.command == 'D') {	/* it shows definition */
		ret = show_probe_trace_events(pevs, npevs);
		goto out_cleanup;
	}

	ret = apply_perf_probe_events(pevs, npevs);
	if (ret < 0)
		goto out_cleanup;

	for (i = k = 0; i < npevs; i++)
		k += pevs[i].ntevs;

	pr_info("Added new event%s\n", (k > 1) ? "s:" : ":");
	for (i = 0; i < npevs; i++) {
		struct perf_probe_event *pev = &pevs[i];

		for (k = 0; k < pev->ntevs; k++) {
			struct probe_trace_event *tev = &pev->tevs[k];

			/* We use tev's name for showing new events */
			show_perf_probe_event(tev->group, tev->event, pev,
					      tev->point.module, false);

			/* Save the last valid name */
			event = tev->event;
			group = tev->group;
		}
	}

	/* Note that it is possible to skip all events because of blacklist */
	if (event) {
		/* Show how to use the event. */
		pr_info("\nYou can now use it in all perf tools, such as:\n\n");
		pr_info("\tperf record -e %s:%s -aR sleep 1\n\n", group, event);
	}

out_cleanup:
	cleanup_perf_probe_events(pevs, npevs);
	exit_probe_symbol_maps();
	return ret;
}