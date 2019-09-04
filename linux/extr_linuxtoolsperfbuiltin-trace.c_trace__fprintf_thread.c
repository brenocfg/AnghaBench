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
struct trace {double nr_events; scalar_t__ sched; } ;
struct thread_trace {double nr_events; double pfmaj; double pfmin; double runtime_ms; } ;
struct thread {int tid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ fputc (char,int /*<<< orphan*/ *) ; 
 char* thread__comm_str (struct thread*) ; 
 scalar_t__ thread__dump_stats (struct thread_trace*,struct trace*,int /*<<< orphan*/ *) ; 
 struct thread_trace* thread__priv (struct thread*) ; 

__attribute__((used)) static size_t trace__fprintf_thread(FILE *fp, struct thread *thread, struct trace *trace)
{
	size_t printed = 0;
	struct thread_trace *ttrace = thread__priv(thread);
	double ratio;

	if (ttrace == NULL)
		return 0;

	ratio = (double)ttrace->nr_events / trace->nr_events * 100.0;

	printed += fprintf(fp, " %s (%d), ", thread__comm_str(thread), thread->tid);
	printed += fprintf(fp, "%lu events, ", ttrace->nr_events);
	printed += fprintf(fp, "%.1f%%", ratio);
	if (ttrace->pfmaj)
		printed += fprintf(fp, ", %lu majfaults", ttrace->pfmaj);
	if (ttrace->pfmin)
		printed += fprintf(fp, ", %lu minfaults", ttrace->pfmin);
	if (trace->sched)
		printed += fprintf(fp, ", %.3f msec\n", ttrace->runtime_ms);
	else if (fputc('\n', fp) != EOF)
		++printed;

	printed += thread__dump_stats(ttrace, trace, fp);

	return printed;
}