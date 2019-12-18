#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; } ;
struct perf_record_auxtrace_info {int /*<<< orphan*/ * priv; int /*<<< orphan*/  type; TYPE_1__ header; } ;
union perf_event {struct perf_record_auxtrace_info auxtrace_info; } ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_10__ {int /*<<< orphan*/  host; } ;
struct perf_session {TYPE_4__* auxtrace; TYPE_5__* itrace_synth_opts; TYPE_2__ machines; } ;
struct TYPE_14__ {scalar_t__ populated; } ;
struct TYPE_13__ {scalar_t__ returns; scalar_t__ calls; int /*<<< orphan*/  thread_stack; int /*<<< orphan*/  default_no_sample; scalar_t__ set; } ;
struct TYPE_12__ {int /*<<< orphan*/  free; int /*<<< orphan*/  free_events; int /*<<< orphan*/  flush_events; int /*<<< orphan*/  process_auxtrace_event; int /*<<< orphan*/  process_event; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_zero; int /*<<< orphan*/  time_mult; int /*<<< orphan*/  time_shift; } ;
struct intel_bts {int sampling_mode; int branches_filter; int data_queued; TYPE_6__ queues; TYPE_5__ synth_opts; TYPE_4__ auxtrace; int /*<<< orphan*/  snapshot_mode; int /*<<< orphan*/  cap_user_time_zero; TYPE_3__ tc; int /*<<< orphan*/  pmu_type; int /*<<< orphan*/  auxtrace_type; int /*<<< orphan*/ * machine; struct perf_session* session; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t INTEL_BTS_CAP_USER_TIME_ZERO ; 
 size_t INTEL_BTS_PMU_TYPE ; 
 int INTEL_BTS_SNAPSHOT_MODE ; 
 size_t INTEL_BTS_TIME_MULT ; 
 size_t INTEL_BTS_TIME_SHIFT ; 
 size_t INTEL_BTS_TIME_ZERO ; 
 int PERF_IP_FLAG_ASYNC ; 
 int PERF_IP_FLAG_CALL ; 
 int PERF_IP_FLAG_RETURN ; 
 int PERF_IP_FLAG_TRACE_BEGIN ; 
 int PERF_IP_FLAG_TRACE_END ; 
 int /*<<< orphan*/  auxtrace_queues__free (TYPE_6__*) ; 
 int auxtrace_queues__init (TYPE_6__*) ; 
 int auxtrace_queues__process_index (TYPE_6__*,struct perf_session*) ; 
 scalar_t__ dump_trace ; 
 int /*<<< orphan*/  free (struct intel_bts*) ; 
 int /*<<< orphan*/  intel_bts_flush ; 
 int /*<<< orphan*/  intel_bts_free ; 
 int /*<<< orphan*/  intel_bts_free_events ; 
 int /*<<< orphan*/  intel_bts_print_info (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  intel_bts_process_auxtrace_event ; 
 int /*<<< orphan*/  intel_bts_process_event ; 
 int intel_bts_synth_events (struct intel_bts*,struct perf_session*) ; 
 int /*<<< orphan*/  itrace_synth_opts__set_default (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct intel_bts* zalloc (int) ; 

int intel_bts_process_auxtrace_info(union perf_event *event,
				    struct perf_session *session)
{
	struct perf_record_auxtrace_info *auxtrace_info = &event->auxtrace_info;
	size_t min_sz = sizeof(u64) * INTEL_BTS_SNAPSHOT_MODE;
	struct intel_bts *bts;
	int err;

	if (auxtrace_info->header.size < sizeof(struct perf_record_auxtrace_info) +
					min_sz)
		return -EINVAL;

	bts = zalloc(sizeof(struct intel_bts));
	if (!bts)
		return -ENOMEM;

	err = auxtrace_queues__init(&bts->queues);
	if (err)
		goto err_free;

	bts->session = session;
	bts->machine = &session->machines.host; /* No kvm support */
	bts->auxtrace_type = auxtrace_info->type;
	bts->pmu_type = auxtrace_info->priv[INTEL_BTS_PMU_TYPE];
	bts->tc.time_shift = auxtrace_info->priv[INTEL_BTS_TIME_SHIFT];
	bts->tc.time_mult = auxtrace_info->priv[INTEL_BTS_TIME_MULT];
	bts->tc.time_zero = auxtrace_info->priv[INTEL_BTS_TIME_ZERO];
	bts->cap_user_time_zero =
			auxtrace_info->priv[INTEL_BTS_CAP_USER_TIME_ZERO];
	bts->snapshot_mode = auxtrace_info->priv[INTEL_BTS_SNAPSHOT_MODE];

	bts->sampling_mode = false;

	bts->auxtrace.process_event = intel_bts_process_event;
	bts->auxtrace.process_auxtrace_event = intel_bts_process_auxtrace_event;
	bts->auxtrace.flush_events = intel_bts_flush;
	bts->auxtrace.free_events = intel_bts_free_events;
	bts->auxtrace.free = intel_bts_free;
	session->auxtrace = &bts->auxtrace;

	intel_bts_print_info(&auxtrace_info->priv[0], INTEL_BTS_PMU_TYPE,
			     INTEL_BTS_SNAPSHOT_MODE);

	if (dump_trace)
		return 0;

	if (session->itrace_synth_opts->set) {
		bts->synth_opts = *session->itrace_synth_opts;
	} else {
		itrace_synth_opts__set_default(&bts->synth_opts,
				session->itrace_synth_opts->default_no_sample);
		bts->synth_opts.thread_stack =
				session->itrace_synth_opts->thread_stack;
	}

	if (bts->synth_opts.calls)
		bts->branches_filter |= PERF_IP_FLAG_CALL | PERF_IP_FLAG_ASYNC |
					PERF_IP_FLAG_TRACE_END;
	if (bts->synth_opts.returns)
		bts->branches_filter |= PERF_IP_FLAG_RETURN |
					PERF_IP_FLAG_TRACE_BEGIN;

	err = intel_bts_synth_events(bts, session);
	if (err)
		goto err_free_queues;

	err = auxtrace_queues__process_index(&bts->queues, session);
	if (err)
		goto err_free_queues;

	if (bts->queues.populated)
		bts->data_queued = true;

	return 0;

err_free_queues:
	auxtrace_queues__free(&bts->queues);
	session->auxtrace = NULL;
err_free:
	free(bts);
	return err;
}