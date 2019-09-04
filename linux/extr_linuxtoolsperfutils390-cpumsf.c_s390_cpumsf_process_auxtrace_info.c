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
struct auxtrace_info_event {int /*<<< orphan*/  type; TYPE_1__ header; } ;
union perf_event {struct auxtrace_info_event auxtrace_info; } ;
struct TYPE_14__ {scalar_t__ populated; } ;
struct TYPE_13__ {int /*<<< orphan*/  free; int /*<<< orphan*/  free_events; int /*<<< orphan*/  flush_events; int /*<<< orphan*/  process_auxtrace_event; int /*<<< orphan*/  process_event; } ;
struct s390_cpumsf {int data_queued; TYPE_6__ queues; TYPE_5__ auxtrace; int /*<<< orphan*/  machine_type; int /*<<< orphan*/  pmu_type; int /*<<< orphan*/  auxtrace_type; int /*<<< orphan*/ * machine; struct perf_session* session; } ;
struct TYPE_10__ {int /*<<< orphan*/  host; } ;
struct perf_session {TYPE_5__* auxtrace; TYPE_4__* evlist; TYPE_2__ machines; int /*<<< orphan*/  itrace_synth_opts; } ;
struct TYPE_12__ {TYPE_3__* env; } ;
struct TYPE_11__ {int /*<<< orphan*/  cpuid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 int /*<<< orphan*/  auxtrace_queues__free (TYPE_6__*) ; 
 int auxtrace_queues__init (TYPE_6__*) ; 
 int auxtrace_queues__process_index (TYPE_6__*,struct perf_session*) ; 
 int /*<<< orphan*/  check_auxtrace_itrace (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_trace ; 
 int /*<<< orphan*/  free (struct s390_cpumsf*) ; 
 int /*<<< orphan*/  s390_cpumsf_flush ; 
 int /*<<< orphan*/  s390_cpumsf_free ; 
 int /*<<< orphan*/  s390_cpumsf_free_events ; 
 int /*<<< orphan*/  s390_cpumsf_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_cpumsf_process_auxtrace_event ; 
 int /*<<< orphan*/  s390_cpumsf_process_event ; 
 struct s390_cpumsf* zalloc (int) ; 

int s390_cpumsf_process_auxtrace_info(union perf_event *event,
				      struct perf_session *session)
{
	struct auxtrace_info_event *auxtrace_info = &event->auxtrace_info;
	struct s390_cpumsf *sf;
	int err;

	if (auxtrace_info->header.size < sizeof(struct auxtrace_info_event))
		return -EINVAL;

	sf = zalloc(sizeof(struct s390_cpumsf));
	if (sf == NULL)
		return -ENOMEM;

	if (!check_auxtrace_itrace(session->itrace_synth_opts)) {
		err = -EINVAL;
		goto err_free;
	}

	err = auxtrace_queues__init(&sf->queues);
	if (err)
		goto err_free;

	sf->session = session;
	sf->machine = &session->machines.host; /* No kvm support */
	sf->auxtrace_type = auxtrace_info->type;
	sf->pmu_type = PERF_TYPE_RAW;
	sf->machine_type = s390_cpumsf_get_type(session->evlist->env->cpuid);

	sf->auxtrace.process_event = s390_cpumsf_process_event;
	sf->auxtrace.process_auxtrace_event = s390_cpumsf_process_auxtrace_event;
	sf->auxtrace.flush_events = s390_cpumsf_flush;
	sf->auxtrace.free_events = s390_cpumsf_free_events;
	sf->auxtrace.free = s390_cpumsf_free;
	session->auxtrace = &sf->auxtrace;

	if (dump_trace)
		return 0;

	err = auxtrace_queues__process_index(&sf->queues, session);
	if (err)
		goto err_free_queues;

	if (sf->queues.populated)
		sf->data_queued = true;

	return 0;

err_free_queues:
	auxtrace_queues__free(&sf->queues);
	session->auxtrace = NULL;
err_free:
	free(sf);
	return err;
}