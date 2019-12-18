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
struct evlist {int /*<<< orphan*/  trace_event_sample_raw; int /*<<< orphan*/  env; } ;

/* Variables and functions */
 char* perf_env__arch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__s390_sample_raw ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

void perf_evlist__init_trace_event_sample_raw(struct evlist *evlist)
{
	const char *arch_pf = perf_env__arch(evlist->env);

	if (arch_pf && !strcmp("s390", arch_pf))
		evlist->trace_event_sample_raw = perf_evlist__s390_sample_raw;
}