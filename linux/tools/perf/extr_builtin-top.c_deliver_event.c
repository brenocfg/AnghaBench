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
struct TYPE_6__ {scalar_t__ type; } ;
union perf_event {TYPE_2__ header; } ;
struct perf_top {int /*<<< orphan*/  tool; int /*<<< orphan*/  guest_us_samples; int /*<<< orphan*/  guest_kernel_samples; int /*<<< orphan*/  hide_kernel_symbols; int /*<<< orphan*/  kernel_samples; int /*<<< orphan*/  hide_user_symbols; int /*<<< orphan*/  us_samples; int /*<<< orphan*/  samples; int /*<<< orphan*/  evswitch; int /*<<< orphan*/  drop_total; int /*<<< orphan*/  drop; struct perf_session* session; struct evlist* evlist; } ;
struct machine {int dummy; } ;
struct TYPE_5__ {struct machine host; } ;
struct perf_session {TYPE_4__* evlist; TYPE_1__ machines; } ;
struct perf_sample {int cpumode; int /*<<< orphan*/  pid; int /*<<< orphan*/  id; } ;
struct ordered_events {struct perf_top* data; } ;
struct ordered_event {union perf_event* event; } ;
struct evsel {int dummy; } ;
struct evlist {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  nr_unknown_events; } ;
struct TYPE_8__ {TYPE_3__ stats; } ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_LOST ; 
 scalar_t__ PERF_RECORD_LOST_SAMPLES ; 
 scalar_t__ PERF_RECORD_MAX ; 
#define  PERF_RECORD_MISC_GUEST_KERNEL 131 
#define  PERF_RECORD_MISC_GUEST_USER 130 
#define  PERF_RECORD_MISC_KERNEL 129 
#define  PERF_RECORD_MISC_USER 128 
 scalar_t__ PERF_RECORD_SAMPLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evsel__hists (struct evsel*) ; 
 scalar_t__ evswitch__discard (int /*<<< orphan*/ *,struct evsel*) ; 
 int /*<<< orphan*/  hists__inc_nr_events (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  machine__process_event (struct machine*,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  perf_event__process_sample (int /*<<< orphan*/ *,union perf_event*,struct evsel*,struct perf_sample*,struct machine*) ; 
 struct evsel* perf_evlist__id2evsel (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int perf_evlist__parse_sample (struct evlist*,union perf_event*,struct perf_sample*) ; 
 struct machine* perf_session__find_machine (struct perf_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_top__process_lost (struct perf_top*,union perf_event*,struct evsel*) ; 
 int /*<<< orphan*/  perf_top__process_lost_samples (struct perf_top*,union perf_event*,struct evsel*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ should_drop (struct ordered_event*,struct perf_top*) ; 

__attribute__((used)) static int deliver_event(struct ordered_events *qe,
			 struct ordered_event *qevent)
{
	struct perf_top *top = qe->data;
	struct evlist *evlist = top->evlist;
	struct perf_session *session = top->session;
	union perf_event *event = qevent->event;
	struct perf_sample sample;
	struct evsel *evsel;
	struct machine *machine;
	int ret = -1;

	if (should_drop(qevent, top)) {
		top->drop++;
		top->drop_total++;
		return 0;
	}

	ret = perf_evlist__parse_sample(evlist, event, &sample);
	if (ret) {
		pr_err("Can't parse sample, err = %d\n", ret);
		goto next_event;
	}

	evsel = perf_evlist__id2evsel(session->evlist, sample.id);
	assert(evsel != NULL);

	if (event->header.type == PERF_RECORD_SAMPLE) {
		if (evswitch__discard(&top->evswitch, evsel))
			return 0;
		++top->samples;
	}

	switch (sample.cpumode) {
	case PERF_RECORD_MISC_USER:
		++top->us_samples;
		if (top->hide_user_symbols)
			goto next_event;
		machine = &session->machines.host;
		break;
	case PERF_RECORD_MISC_KERNEL:
		++top->kernel_samples;
		if (top->hide_kernel_symbols)
			goto next_event;
		machine = &session->machines.host;
		break;
	case PERF_RECORD_MISC_GUEST_KERNEL:
		++top->guest_kernel_samples;
		machine = perf_session__find_machine(session,
						     sample.pid);
		break;
	case PERF_RECORD_MISC_GUEST_USER:
		++top->guest_us_samples;
		/*
		 * TODO: we don't process guest user from host side
		 * except simple counting.
		 */
		goto next_event;
	default:
		if (event->header.type == PERF_RECORD_SAMPLE)
			goto next_event;
		machine = &session->machines.host;
		break;
	}

	if (event->header.type == PERF_RECORD_SAMPLE) {
		perf_event__process_sample(&top->tool, event, evsel,
					   &sample, machine);
	} else if (event->header.type == PERF_RECORD_LOST) {
		perf_top__process_lost(top, event, evsel);
	} else if (event->header.type == PERF_RECORD_LOST_SAMPLES) {
		perf_top__process_lost_samples(top, event, evsel);
	} else if (event->header.type < PERF_RECORD_MAX) {
		hists__inc_nr_events(evsel__hists(evsel), event->header.type);
		machine__process_event(machine, event, &sample);
	} else
		++session->evlist->stats.nr_unknown_events;

	ret = 0;
next_event:
	return ret;
}