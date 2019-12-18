#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct perf_session {struct evlist* evlist; } ;
struct perf_event_attr {int size; int sample_type; int sample_period; void* config; int /*<<< orphan*/  type; int /*<<< orphan*/  read_format; int /*<<< orphan*/  sample_id_all; int /*<<< orphan*/  exclude_guest; int /*<<< orphan*/  exclude_host; int /*<<< orphan*/  exclude_hv; int /*<<< orphan*/  exclude_kernel; int /*<<< orphan*/  exclude_user; } ;
struct TYPE_6__ {scalar_t__ period_type; int period; scalar_t__ pwr_events; scalar_t__ ptwrites; scalar_t__ transactions; scalar_t__ instructions; scalar_t__ last_branch; scalar_t__ callchain; scalar_t__ branches; } ;
struct intel_pt {int sample_branches; int branches_sample_type; int branches_id; int sample_instructions; int instructions_sample_type; int instructions_id; int sample_transactions; int transactions_sample_type; int transactions_id; int sample_ptwrites; int ptwrites_sample_type; int ptwrites_id; int sample_pwr_events; int pwr_events_sample_type; int cbr_id; int mwait_id; int pwre_id; int exstop_id; int pwrx_id; TYPE_3__ synth_opts; int /*<<< orphan*/  per_cpu_mmaps; scalar_t__ timeless_decoding; } ;
struct TYPE_4__ {int sample_type; int config; int /*<<< orphan*/  read_format; int /*<<< orphan*/  sample_id_all; int /*<<< orphan*/  exclude_guest; int /*<<< orphan*/  exclude_host; int /*<<< orphan*/  exclude_hv; int /*<<< orphan*/  exclude_kernel; int /*<<< orphan*/  exclude_user; } ;
struct TYPE_5__ {int* id; TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 void* PERF_COUNT_HW_BRANCH_INSTRUCTIONS ; 
 void* PERF_COUNT_HW_INSTRUCTIONS ; 
 scalar_t__ PERF_ITRACE_PERIOD_NANOSECS ; 
 int PERF_SAMPLE_ADDR ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 scalar_t__ PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_MASK ; 
 int PERF_SAMPLE_PERIOD ; 
 int PERF_SAMPLE_RAW ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 void* PERF_SYNTH_INTEL_CBR ; 
 void* PERF_SYNTH_INTEL_EXSTOP ; 
 void* PERF_SYNTH_INTEL_MWAIT ; 
 void* PERF_SYNTH_INTEL_PTWRITE ; 
 void* PERF_SYNTH_INTEL_PWRE ; 
 void* PERF_SYNTH_INTEL_PWRX ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  PERF_TYPE_SYNTH ; 
 struct evsel* intel_pt_evsel (struct intel_pt*,struct evlist*) ; 
 int intel_pt_ns_to_ticks (struct intel_pt*,int) ; 
 int /*<<< orphan*/  intel_pt_set_event_name (struct evlist*,int,char*) ; 
 int intel_pt_synth_event (struct perf_session*,char*,struct perf_event_attr*,int) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int intel_pt_synth_events(struct intel_pt *pt,
				 struct perf_session *session)
{
	struct evlist *evlist = session->evlist;
	struct evsel *evsel = intel_pt_evsel(pt, evlist);
	struct perf_event_attr attr;
	u64 id;
	int err;

	if (!evsel) {
		pr_debug("There are no selected events with Intel Processor Trace data\n");
		return 0;
	}

	memset(&attr, 0, sizeof(struct perf_event_attr));
	attr.size = sizeof(struct perf_event_attr);
	attr.type = PERF_TYPE_HARDWARE;
	attr.sample_type = evsel->core.attr.sample_type & PERF_SAMPLE_MASK;
	attr.sample_type |= PERF_SAMPLE_IP | PERF_SAMPLE_TID |
			    PERF_SAMPLE_PERIOD;
	if (pt->timeless_decoding)
		attr.sample_type &= ~(u64)PERF_SAMPLE_TIME;
	else
		attr.sample_type |= PERF_SAMPLE_TIME;
	if (!pt->per_cpu_mmaps)
		attr.sample_type &= ~(u64)PERF_SAMPLE_CPU;
	attr.exclude_user = evsel->core.attr.exclude_user;
	attr.exclude_kernel = evsel->core.attr.exclude_kernel;
	attr.exclude_hv = evsel->core.attr.exclude_hv;
	attr.exclude_host = evsel->core.attr.exclude_host;
	attr.exclude_guest = evsel->core.attr.exclude_guest;
	attr.sample_id_all = evsel->core.attr.sample_id_all;
	attr.read_format = evsel->core.attr.read_format;

	id = evsel->core.id[0] + 1000000000;
	if (!id)
		id = 1;

	if (pt->synth_opts.branches) {
		attr.config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
		attr.sample_period = 1;
		attr.sample_type |= PERF_SAMPLE_ADDR;
		err = intel_pt_synth_event(session, "branches", &attr, id);
		if (err)
			return err;
		pt->sample_branches = true;
		pt->branches_sample_type = attr.sample_type;
		pt->branches_id = id;
		id += 1;
		attr.sample_type &= ~(u64)PERF_SAMPLE_ADDR;
	}

	if (pt->synth_opts.callchain)
		attr.sample_type |= PERF_SAMPLE_CALLCHAIN;
	if (pt->synth_opts.last_branch)
		attr.sample_type |= PERF_SAMPLE_BRANCH_STACK;

	if (pt->synth_opts.instructions) {
		attr.config = PERF_COUNT_HW_INSTRUCTIONS;
		if (pt->synth_opts.period_type == PERF_ITRACE_PERIOD_NANOSECS)
			attr.sample_period =
				intel_pt_ns_to_ticks(pt, pt->synth_opts.period);
		else
			attr.sample_period = pt->synth_opts.period;
		err = intel_pt_synth_event(session, "instructions", &attr, id);
		if (err)
			return err;
		pt->sample_instructions = true;
		pt->instructions_sample_type = attr.sample_type;
		pt->instructions_id = id;
		id += 1;
	}

	attr.sample_type &= ~(u64)PERF_SAMPLE_PERIOD;
	attr.sample_period = 1;

	if (pt->synth_opts.transactions) {
		attr.config = PERF_COUNT_HW_INSTRUCTIONS;
		err = intel_pt_synth_event(session, "transactions", &attr, id);
		if (err)
			return err;
		pt->sample_transactions = true;
		pt->transactions_sample_type = attr.sample_type;
		pt->transactions_id = id;
		intel_pt_set_event_name(evlist, id, "transactions");
		id += 1;
	}

	attr.type = PERF_TYPE_SYNTH;
	attr.sample_type |= PERF_SAMPLE_RAW;

	if (pt->synth_opts.ptwrites) {
		attr.config = PERF_SYNTH_INTEL_PTWRITE;
		err = intel_pt_synth_event(session, "ptwrite", &attr, id);
		if (err)
			return err;
		pt->sample_ptwrites = true;
		pt->ptwrites_sample_type = attr.sample_type;
		pt->ptwrites_id = id;
		intel_pt_set_event_name(evlist, id, "ptwrite");
		id += 1;
	}

	if (pt->synth_opts.pwr_events) {
		pt->sample_pwr_events = true;
		pt->pwr_events_sample_type = attr.sample_type;

		attr.config = PERF_SYNTH_INTEL_CBR;
		err = intel_pt_synth_event(session, "cbr", &attr, id);
		if (err)
			return err;
		pt->cbr_id = id;
		intel_pt_set_event_name(evlist, id, "cbr");
		id += 1;
	}

	if (pt->synth_opts.pwr_events && (evsel->core.attr.config & 0x10)) {
		attr.config = PERF_SYNTH_INTEL_MWAIT;
		err = intel_pt_synth_event(session, "mwait", &attr, id);
		if (err)
			return err;
		pt->mwait_id = id;
		intel_pt_set_event_name(evlist, id, "mwait");
		id += 1;

		attr.config = PERF_SYNTH_INTEL_PWRE;
		err = intel_pt_synth_event(session, "pwre", &attr, id);
		if (err)
			return err;
		pt->pwre_id = id;
		intel_pt_set_event_name(evlist, id, "pwre");
		id += 1;

		attr.config = PERF_SYNTH_INTEL_EXSTOP;
		err = intel_pt_synth_event(session, "exstop", &attr, id);
		if (err)
			return err;
		pt->exstop_id = id;
		intel_pt_set_event_name(evlist, id, "exstop");
		id += 1;

		attr.config = PERF_SYNTH_INTEL_PWRX;
		err = intel_pt_synth_event(session, "pwrx", &attr, id);
		if (err)
			return err;
		pt->pwrx_id = id;
		intel_pt_set_event_name(evlist, id, "pwrx");
		id += 1;
	}

	return 0;
}