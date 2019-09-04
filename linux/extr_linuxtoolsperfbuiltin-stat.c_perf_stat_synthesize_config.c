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
struct TYPE_5__ {int /*<<< orphan*/  cpus; int /*<<< orphan*/  threads; } ;
struct TYPE_4__ {int /*<<< orphan*/  session; } ;

/* Variables and functions */
 TYPE_2__* evsel_list ; 
 int perf_event__synthesize_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_event__synthesize_cpu_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perf_event__synthesize_extra_attr (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int perf_event__synthesize_stat_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perf_event__synthesize_thread_map2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ perf_stat ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  process_synthesized_event ; 
 int /*<<< orphan*/  stat_config ; 

__attribute__((used)) static int perf_stat_synthesize_config(bool is_pipe)
{
	int err;

	if (is_pipe) {
		err = perf_event__synthesize_attrs(NULL, perf_stat.session,
						   process_synthesized_event);
		if (err < 0) {
			pr_err("Couldn't synthesize attrs.\n");
			return err;
		}
	}

	err = perf_event__synthesize_extra_attr(NULL,
						evsel_list,
						process_synthesized_event,
						is_pipe);

	err = perf_event__synthesize_thread_map2(NULL, evsel_list->threads,
						process_synthesized_event,
						NULL);
	if (err < 0) {
		pr_err("Couldn't synthesize thread map.\n");
		return err;
	}

	err = perf_event__synthesize_cpu_map(NULL, evsel_list->cpus,
					     process_synthesized_event, NULL);
	if (err < 0) {
		pr_err("Couldn't synthesize thread map.\n");
		return err;
	}

	err = perf_event__synthesize_stat_config(NULL, &stat_config,
						 process_synthesized_event, NULL);
	if (err < 0) {
		pr_err("Couldn't synthesize config.\n");
		return err;
	}

	return 0;
}