#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
union perf_event {TYPE_1__ itrace_start; } ;
struct thread {int dummy; } ;
struct cs_etm_auxtrace {int /*<<< orphan*/  machine; scalar_t__ timeless_decoding; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct thread* machine__findnew_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

__attribute__((used)) static int cs_etm__process_itrace_start(struct cs_etm_auxtrace *etm,
					union perf_event *event)
{
	struct thread *th;

	if (etm->timeless_decoding)
		return 0;

	/*
	 * Add the tid/pid to the log so that we can get a match when
	 * we get a contextID from the decoder.
	 */
	th = machine__findnew_thread(etm->machine,
				     event->itrace_start.pid,
				     event->itrace_start.tid);
	if (!th)
		return -ENOMEM;

	thread__put(th);

	return 0;
}