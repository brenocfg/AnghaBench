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
union perf_event {int /*<<< orphan*/  auxtrace_error; } ;
typedef  int /*<<< orphan*/  u64 ;
struct s390_cpumsf {int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int MAX_AUXTRACE_ERROR_MSG ; 
 int /*<<< orphan*/  PERF_AUXTRACE_ERROR_ITRACE ; 
 int /*<<< orphan*/  auxtrace_synth_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int perf_session__deliver_synth_event (int /*<<< orphan*/ ,union perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int s390_cpumsf_synth_error(struct s390_cpumsf *sf, int code, int cpu,
				   pid_t pid, pid_t tid, u64 ip, u64 timestamp)
{
	char msg[MAX_AUXTRACE_ERROR_MSG];
	union perf_event event;
	int err;

	strncpy(msg, "Lost Auxiliary Trace Buffer", sizeof(msg) - 1);
	auxtrace_synth_error(&event.auxtrace_error, PERF_AUXTRACE_ERROR_ITRACE,
			     code, cpu, pid, tid, ip, msg, timestamp);

	err = perf_session__deliver_synth_event(sf->session, &event, NULL);
	if (err)
		pr_err("s390 Auxiliary Trace: failed to deliver error event,"
			"error %d\n", err);
	return err;
}