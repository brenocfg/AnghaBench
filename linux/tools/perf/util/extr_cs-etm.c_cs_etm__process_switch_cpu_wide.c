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
struct TYPE_4__ {int /*<<< orphan*/  next_prev_tid; int /*<<< orphan*/  next_prev_pid; } ;
struct TYPE_3__ {int misc; } ;
union perf_event {TYPE_2__ context_switch; TYPE_1__ header; } ;
struct thread {int dummy; } ;
struct cs_etm_auxtrace {int /*<<< orphan*/  machine; scalar_t__ timeless_decoding; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PERF_RECORD_MISC_SWITCH_OUT ; 
 struct thread* machine__findnew_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

__attribute__((used)) static int cs_etm__process_switch_cpu_wide(struct cs_etm_auxtrace *etm,
					   union perf_event *event)
{
	struct thread *th;
	bool out = event->header.misc & PERF_RECORD_MISC_SWITCH_OUT;

	/*
	 * Context switch in per-thread mode are irrelevant since perf
	 * will start/stop tracing as the process is scheduled.
	 */
	if (etm->timeless_decoding)
		return 0;

	/*
	 * SWITCH_IN events carry the next process to be switched out while
	 * SWITCH_OUT events carry the process to be switched in.  As such
	 * we don't care about IN events.
	 */
	if (!out)
		return 0;

	/*
	 * Add the tid/pid to the log so that we can get a match when
	 * we get a contextID from the decoder.
	 */
	th = machine__findnew_thread(etm->machine,
				     event->context_switch.next_prev_pid,
				     event->context_switch.next_prev_tid);
	if (!th)
		return -ENOMEM;

	thread__put(th);

	return 0;
}