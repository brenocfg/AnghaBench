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
struct evsel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct evsel*) ; 
 int /*<<< orphan*/  evsel__delete_priv (struct evsel*) ; 
 scalar_t__ perf_evsel__init_raw_syscall_tp (struct evsel*,void*) ; 
 struct evsel* perf_evsel__newtp (char*,char const*) ; 

__attribute__((used)) static struct evsel *perf_evsel__raw_syscall_newtp(const char *direction, void *handler)
{
	struct evsel *evsel = perf_evsel__newtp("raw_syscalls", direction);

	/* older kernel (e.g., RHEL6) use syscalls:{enter,exit} */
	if (IS_ERR(evsel))
		evsel = perf_evsel__newtp("syscalls", direction);

	if (IS_ERR(evsel))
		return NULL;

	if (perf_evsel__init_raw_syscall_tp(evsel, handler))
		goto out_delete;

	return evsel;

out_delete:
	evsel__delete_priv(evsel);
	return NULL;
}