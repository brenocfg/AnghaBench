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
struct trace {int /*<<< orphan*/  output; int /*<<< orphan*/  raw_augmented_syscalls_args_size; int /*<<< orphan*/  host; } ;
struct thread_trace {int dummy; } ;
struct thread {int dummy; } ;
struct syscall {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct evsel {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int id ; 
 struct thread* machine__findnew_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* perf_evsel__sc_tp_ptr (struct evsel*,void*,struct perf_sample*) ; 
 int perf_evsel__sc_tp_uint (struct evsel*,int /*<<< orphan*/ ,struct perf_sample*) ; 
 void* syscall__augmented_args (struct syscall*,struct perf_sample*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall__scnprintf_args (struct syscall*,char*,int,void*,void*,int,struct trace*,struct thread*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 
 struct thread_trace* thread__trace (struct thread*,int /*<<< orphan*/ ) ; 
 struct syscall* trace__syscall_info (struct trace*,struct evsel*,int) ; 

__attribute__((used)) static int trace__fprintf_sys_enter(struct trace *trace, struct evsel *evsel,
				    struct perf_sample *sample)
{
	struct thread_trace *ttrace;
	struct thread *thread;
	int id = perf_evsel__sc_tp_uint(evsel, id, sample), err = -1;
	struct syscall *sc = trace__syscall_info(trace, evsel, id);
	char msg[1024];
	void *args, *augmented_args = NULL;
	int augmented_args_size;

	if (sc == NULL)
		return -1;

	thread = machine__findnew_thread(trace->host, sample->pid, sample->tid);
	ttrace = thread__trace(thread, trace->output);
	/*
	 * We need to get ttrace just to make sure it is there when syscall__scnprintf_args()
	 * and the rest of the beautifiers accessing it via struct syscall_arg touches it.
	 */
	if (ttrace == NULL)
		goto out_put;

	args = perf_evsel__sc_tp_ptr(evsel, args, sample);
	augmented_args = syscall__augmented_args(sc, sample, &augmented_args_size, trace->raw_augmented_syscalls_args_size);
	syscall__scnprintf_args(sc, msg, sizeof(msg), args, augmented_args, augmented_args_size, trace, thread);
	fprintf(trace->output, "%s", msg);
	err = 0;
out_put:
	thread__put(thread);
	return err;
}