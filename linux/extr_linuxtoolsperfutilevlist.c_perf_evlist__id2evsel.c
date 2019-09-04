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
typedef  int /*<<< orphan*/  u64 ;
struct perf_sample_id {struct perf_evsel* evsel; } ;
struct perf_evsel {int dummy; } ;
struct perf_evlist {int nr_entries; } ;

/* Variables and functions */
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 
 struct perf_sample_id* perf_evlist__id2sid (struct perf_evlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__sample_id_all (struct perf_evlist*) ; 

struct perf_evsel *perf_evlist__id2evsel(struct perf_evlist *evlist, u64 id)
{
	struct perf_sample_id *sid;

	if (evlist->nr_entries == 1 || !id)
		return perf_evlist__first(evlist);

	sid = perf_evlist__id2sid(evlist, id);
	if (sid)
		return sid->evsel;

	if (!perf_evlist__sample_id_all(evlist))
		return perf_evlist__first(evlist);

	return NULL;
}