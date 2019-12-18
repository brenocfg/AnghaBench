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
struct TYPE_4__ {int size; } ;
struct perf_record_auxtrace_info {int /*<<< orphan*/ * priv; int /*<<< orphan*/  type; TYPE_1__ header; } ;
union perf_event {struct perf_record_auxtrace_info auxtrace_info; } ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;
struct perf_session {TYPE_3__* auxtrace; TYPE_2__ machines; } ;
struct TYPE_6__ {int /*<<< orphan*/  free; int /*<<< orphan*/  free_events; int /*<<< orphan*/  flush_events; int /*<<< orphan*/  process_auxtrace_event; int /*<<< orphan*/  process_event; } ;
struct arm_spe {TYPE_3__ auxtrace; int /*<<< orphan*/  pmu_type; int /*<<< orphan*/  auxtrace_type; int /*<<< orphan*/ * machine; struct perf_session* session; int /*<<< orphan*/  queues; } ;

/* Variables and functions */
 int ARM_SPE_PMU_TYPE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  arm_spe_flush ; 
 int /*<<< orphan*/  arm_spe_free ; 
 int /*<<< orphan*/  arm_spe_free_events ; 
 int /*<<< orphan*/  arm_spe_print_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_spe_process_auxtrace_event ; 
 int /*<<< orphan*/  arm_spe_process_event ; 
 int auxtrace_queues__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct arm_spe*) ; 
 struct arm_spe* zalloc (int) ; 

int arm_spe_process_auxtrace_info(union perf_event *event,
				  struct perf_session *session)
{
	struct perf_record_auxtrace_info *auxtrace_info = &event->auxtrace_info;
	size_t min_sz = sizeof(u64) * ARM_SPE_PMU_TYPE;
	struct arm_spe *spe;
	int err;

	if (auxtrace_info->header.size < sizeof(struct perf_record_auxtrace_info) +
					min_sz)
		return -EINVAL;

	spe = zalloc(sizeof(struct arm_spe));
	if (!spe)
		return -ENOMEM;

	err = auxtrace_queues__init(&spe->queues);
	if (err)
		goto err_free;

	spe->session = session;
	spe->machine = &session->machines.host; /* No kvm support */
	spe->auxtrace_type = auxtrace_info->type;
	spe->pmu_type = auxtrace_info->priv[ARM_SPE_PMU_TYPE];

	spe->auxtrace.process_event = arm_spe_process_event;
	spe->auxtrace.process_auxtrace_event = arm_spe_process_auxtrace_event;
	spe->auxtrace.flush_events = arm_spe_flush;
	spe->auxtrace.free_events = arm_spe_free_events;
	spe->auxtrace.free = arm_spe_free;
	session->auxtrace = &spe->auxtrace;

	arm_spe_print_info(&auxtrace_info->priv[0]);

	return 0;

err_free:
	free(spe);
	return err;
}