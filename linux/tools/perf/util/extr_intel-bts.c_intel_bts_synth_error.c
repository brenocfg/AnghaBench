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
struct intel_bts {int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_BTS_ERR_NOINSN ; 
 int /*<<< orphan*/  PERF_AUXTRACE_ERROR_ITRACE ; 
 int /*<<< orphan*/  auxtrace_synth_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int perf_session__deliver_synth_event (int /*<<< orphan*/ ,union perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int intel_bts_synth_error(struct intel_bts *bts, int cpu, pid_t pid,
				 pid_t tid, u64 ip)
{
	union perf_event event;
	int err;

	auxtrace_synth_error(&event.auxtrace_error, PERF_AUXTRACE_ERROR_ITRACE,
			     INTEL_BTS_ERR_NOINSN, cpu, pid, tid, ip,
			     "Failed to get instruction", 0);

	err = perf_session__deliver_synth_event(bts->session, &event, NULL);
	if (err)
		pr_err("Intel BTS: failed to deliver error event, error %d\n",
		       err);

	return err;
}