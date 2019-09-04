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
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_evsel*) ; 
 int PTR_ERR (struct perf_evsel*) ; 
 struct perf_evsel* bpf__setup_output_event (struct perf_evlist*,char*) ; 

int bpf__setup_stdout(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = bpf__setup_output_event(evlist, "__bpf_stdout__");
	return IS_ERR(evsel) ? PTR_ERR(evsel) : 0;
}