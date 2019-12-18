#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct perf_event {int /*<<< orphan*/  pending; int /*<<< orphan*/  pending_disable; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_work_queue_on (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_event_disable_local (struct perf_event*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void perf_pending_event_disable(struct perf_event *event)
{
	int cpu = READ_ONCE(event->pending_disable);

	if (cpu < 0)
		return;

	if (cpu == smp_processor_id()) {
		WRITE_ONCE(event->pending_disable, -1);
		perf_event_disable_local(event);
		return;
	}

	/*
	 *  CPU-A			CPU-B
	 *
	 *  perf_event_disable_inatomic()
	 *    @pending_disable = CPU-A;
	 *    irq_work_queue();
	 *
	 *  sched-out
	 *    @pending_disable = -1;
	 *
	 *				sched-in
	 *				perf_event_disable_inatomic()
	 *				  @pending_disable = CPU-B;
	 *				  irq_work_queue(); // FAILS
	 *
	 *  irq_work_run()
	 *    perf_pending_event()
	 *
	 * But the event runs on CPU-B and wants disabling there.
	 */
	irq_work_queue_on(&event->pending, cpu);
}