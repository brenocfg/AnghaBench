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
union perf_event {int /*<<< orphan*/  thread_map; } ;
struct perf_thread_map {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 
 scalar_t__ thread_map__fprintf (struct perf_thread_map*,int /*<<< orphan*/ *) ; 
 struct perf_thread_map* thread_map__new_event (int /*<<< orphan*/ *) ; 

size_t perf_event__fprintf_thread_map(union perf_event *event, FILE *fp)
{
	struct perf_thread_map *threads = thread_map__new_event(&event->thread_map);
	size_t ret;

	ret = fprintf(fp, " nr: ");

	if (threads)
		ret += thread_map__fprintf(threads, fp);
	else
		ret += fprintf(fp, "failed to get threads from event\n");

	perf_thread_map__put(threads);
	return ret;
}