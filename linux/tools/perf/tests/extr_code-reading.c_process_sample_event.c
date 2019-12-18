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
typedef  union perf_event {int dummy; } perf_event ;
struct thread {int dummy; } ;
struct state {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  cpumode; int /*<<< orphan*/  ip; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct machine {int dummy; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READLEN ; 
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evlist__parse_sample (struct evlist*,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int read_object_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,struct state*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

__attribute__((used)) static int process_sample_event(struct machine *machine,
				struct evlist *evlist,
				union perf_event *event, struct state *state)
{
	struct perf_sample sample;
	struct thread *thread;
	int ret;

	if (perf_evlist__parse_sample(evlist, event, &sample)) {
		pr_debug("perf_evlist__parse_sample failed\n");
		return -1;
	}

	thread = machine__findnew_thread(machine, sample.pid, sample.tid);
	if (!thread) {
		pr_debug("machine__findnew_thread failed\n");
		return -1;
	}

	ret = read_object_code(sample.ip, READLEN, sample.cpumode, thread, state);
	thread__put(thread);
	return ret;
}