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
typedef  int /*<<< orphan*/  u32 ;
struct perf_sample_id {int /*<<< orphan*/  id; } ;
struct perf_counts_values {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 struct perf_sample_id* SID (struct evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_event__synthesize_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_counts_values*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_synthesized_event ; 

__attribute__((used)) static int
perf_evsel__write_stat_event(struct evsel *counter, u32 cpu, u32 thread,
			     struct perf_counts_values *count)
{
	struct perf_sample_id *sid = SID(counter, cpu, thread);

	return perf_event__synthesize_stat(NULL, cpu, thread, sid->id, count,
					   process_synthesized_event, NULL);
}