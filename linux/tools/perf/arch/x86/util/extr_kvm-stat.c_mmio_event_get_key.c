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
struct perf_sample {int dummy; } ;
struct evsel {int dummy; } ;
struct event_key {void* info; void* key; } ;

/* Variables and functions */
 void* perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 

__attribute__((used)) static void mmio_event_get_key(struct evsel *evsel, struct perf_sample *sample,
			       struct event_key *key)
{
	key->key  = perf_evsel__intval(evsel, sample, "gpa");
	key->info = perf_evsel__intval(evsel, sample, "type");
}