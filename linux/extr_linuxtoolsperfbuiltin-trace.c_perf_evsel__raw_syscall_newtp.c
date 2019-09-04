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
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__delete_priv (struct perf_evsel*) ; 
 scalar_t__ perf_evsel__init_raw_syscall_tp (struct perf_evsel*,void*) ; 
 struct perf_evsel* perf_evsel__newtp (char*,char const*) ; 

__attribute__((used)) static struct perf_evsel *perf_evsel__raw_syscall_newtp(const char *direction, void *handler)
{
	struct perf_evsel *evsel = perf_evsel__newtp("raw_syscalls", direction);

	/* older kernel (e.g., RHEL6) use syscalls:{enter,exit} */
	if (IS_ERR(evsel))
		evsel = perf_evsel__newtp("syscalls", direction);

	if (IS_ERR(evsel))
		return NULL;

	if (perf_evsel__init_raw_syscall_tp(evsel, handler))
		goto out_delete;

	return evsel;

out_delete:
	perf_evsel__delete_priv(evsel);
	return NULL;
}