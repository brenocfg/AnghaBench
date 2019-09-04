#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct perf_event_attr {int read_format; int inherit; int disabled; int enable_on_exec; int /*<<< orphan*/  sample_type; scalar_t__ sample_period; } ;
struct perf_evsel {int nr_members; struct perf_evsel* leader; struct perf_event_attr attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  threads; } ;
struct TYPE_5__ {scalar_t__ is_pipe; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
struct TYPE_6__ {scalar_t__ scale; } ;

/* Variables and functions */
 int PERF_FORMAT_GROUP ; 
 int PERF_FORMAT_ID ; 
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 int /*<<< orphan*/  PERF_SAMPLE_IDENTIFIER ; 
 scalar_t__ STAT_RECORD ; 
 TYPE_4__* evsel_list ; 
 int /*<<< orphan*/  initial_delay ; 
 int /*<<< orphan*/  no_inherit ; 
 int /*<<< orphan*/  perf_evsel__cpus (struct perf_evsel*) ; 
 scalar_t__ perf_evsel__is_group_leader (struct perf_evsel*) ; 
 int perf_evsel__open_per_cpu (struct perf_evsel*,int /*<<< orphan*/ ) ; 
 int perf_evsel__open_per_thread (struct perf_evsel*,int /*<<< orphan*/ ) ; 
 TYPE_3__ perf_stat ; 
 TYPE_2__ stat_config ; 
 int /*<<< orphan*/  target ; 
 scalar_t__ target__has_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target__has_per_thread (int /*<<< orphan*/ *) ; 
 scalar_t__ target__none (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_perf_stat_counter(struct perf_evsel *evsel)
{
	struct perf_event_attr *attr = &evsel->attr;
	struct perf_evsel *leader = evsel->leader;

	if (stat_config.scale) {
		attr->read_format = PERF_FORMAT_TOTAL_TIME_ENABLED |
				    PERF_FORMAT_TOTAL_TIME_RUNNING;
	}

	/*
	 * The event is part of non trivial group, let's enable
	 * the group read (for leader) and ID retrieval for all
	 * members.
	 */
	if (leader->nr_members > 1)
		attr->read_format |= PERF_FORMAT_ID|PERF_FORMAT_GROUP;

	attr->inherit = !no_inherit;

	/*
	 * Some events get initialized with sample_(period/type) set,
	 * like tracepoints. Clear it up for counting.
	 */
	attr->sample_period = 0;

	/*
	 * But set sample_type to PERF_SAMPLE_IDENTIFIER, which should be harmless
	 * while avoiding that older tools show confusing messages.
	 *
	 * However for pipe sessions we need to keep it zero,
	 * because script's perf_evsel__check_attr is triggered
	 * by attr->sample_type != 0, and we can't run it on
	 * stat sessions.
	 */
	if (!(STAT_RECORD && perf_stat.data.is_pipe))
		attr->sample_type = PERF_SAMPLE_IDENTIFIER;

	/*
	 * Disabling all counters initially, they will be enabled
	 * either manually by us or by kernel via enable_on_exec
	 * set later.
	 */
	if (perf_evsel__is_group_leader(evsel)) {
		attr->disabled = 1;

		/*
		 * In case of initial_delay we enable tracee
		 * events manually.
		 */
		if (target__none(&target) && !initial_delay)
			attr->enable_on_exec = 1;
	}

	if (target__has_cpu(&target) && !target__has_per_thread(&target))
		return perf_evsel__open_per_cpu(evsel, perf_evsel__cpus(evsel));

	return perf_evsel__open_per_thread(evsel, evsel_list->threads);
}