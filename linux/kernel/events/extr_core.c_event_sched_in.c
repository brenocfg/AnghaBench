#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct perf_event_context {int /*<<< orphan*/  nr_freq; int /*<<< orphan*/  nr_active; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {scalar_t__ exclusive; scalar_t__ sample_freq; scalar_t__ freq; } ;
struct TYPE_5__ {scalar_t__ interrupts; } ;
struct perf_event {scalar_t__ state; int oncpu; TYPE_3__* pmu; TYPE_2__ attr; TYPE_1__ hw; } ;
struct perf_cpu_context {int exclusive; int /*<<< orphan*/  active_oncpu; } ;
struct TYPE_7__ {scalar_t__ (* add ) (struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ MAX_INTERRUPTS ; 
 int /*<<< orphan*/  PERF_EF_START ; 
 int /*<<< orphan*/  PERF_EVENT_STATE_ACTIVE ; 
 int /*<<< orphan*/  PERF_EVENT_STATE_INACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_software_event (struct perf_event*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_ctx_activate (struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_event_set_state (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_log_itrace_start (struct perf_event*) ; 
 int /*<<< orphan*/  perf_log_throttle (struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_pmu_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  perf_pmu_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  perf_set_shadow_time (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ stub1 (struct perf_event*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
event_sched_in(struct perf_event *event,
		 struct perf_cpu_context *cpuctx,
		 struct perf_event_context *ctx)
{
	int ret = 0;

	lockdep_assert_held(&ctx->lock);

	if (event->state <= PERF_EVENT_STATE_OFF)
		return 0;

	WRITE_ONCE(event->oncpu, smp_processor_id());
	/*
	 * Order event::oncpu write to happen before the ACTIVE state is
	 * visible. This allows perf_event_{stop,read}() to observe the correct
	 * ->oncpu if it sees ACTIVE.
	 */
	smp_wmb();
	perf_event_set_state(event, PERF_EVENT_STATE_ACTIVE);

	/*
	 * Unthrottle events, since we scheduled we might have missed several
	 * ticks already, also for a heavily scheduling task there is little
	 * guarantee it'll get a tick in a timely manner.
	 */
	if (unlikely(event->hw.interrupts == MAX_INTERRUPTS)) {
		perf_log_throttle(event, 1);
		event->hw.interrupts = 0;
	}

	perf_pmu_disable(event->pmu);

	perf_set_shadow_time(event, ctx);

	perf_log_itrace_start(event);

	if (event->pmu->add(event, PERF_EF_START)) {
		perf_event_set_state(event, PERF_EVENT_STATE_INACTIVE);
		event->oncpu = -1;
		ret = -EAGAIN;
		goto out;
	}

	if (!is_software_event(event))
		cpuctx->active_oncpu++;
	if (!ctx->nr_active++)
		perf_event_ctx_activate(ctx);
	if (event->attr.freq && event->attr.sample_freq)
		ctx->nr_freq++;

	if (event->attr.exclusive)
		cpuctx->exclusive = 1;

out:
	perf_pmu_enable(event->pmu);

	return ret;
}