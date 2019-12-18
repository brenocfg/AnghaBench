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
struct perf_sample {int /*<<< orphan*/  cpu; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 scalar_t__ insert_alloc_stat (unsigned long,unsigned long,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ insert_caller_stat (unsigned long,int,int) ; 
 int /*<<< orphan*/  nr_allocs ; 
 void* perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int total_allocated ; 
 int total_requested ; 

__attribute__((used)) static int perf_evsel__process_alloc_event(struct evsel *evsel,
					   struct perf_sample *sample)
{
	unsigned long ptr = perf_evsel__intval(evsel, sample, "ptr"),
		      call_site = perf_evsel__intval(evsel, sample, "call_site");
	int bytes_req = perf_evsel__intval(evsel, sample, "bytes_req"),
	    bytes_alloc = perf_evsel__intval(evsel, sample, "bytes_alloc");

	if (insert_alloc_stat(call_site, ptr, bytes_req, bytes_alloc, sample->cpu) ||
	    insert_caller_stat(call_site, bytes_req, bytes_alloc))
		return -1;

	total_requested += bytes_req;
	total_allocated += bytes_alloc;

	nr_allocs++;
	return 0;
}