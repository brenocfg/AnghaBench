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
struct thread_trace {int /*<<< orphan*/  nr_events; } ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COLOR_RED ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct thread_trace* thread__priv (struct thread*) ; 
 int /*<<< orphan*/  thread__set_priv (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_trace__new () ; 

__attribute__((used)) static struct thread_trace *thread__trace(struct thread *thread, FILE *fp)
{
	struct thread_trace *ttrace;

	if (thread == NULL)
		goto fail;

	if (thread__priv(thread) == NULL)
		thread__set_priv(thread, thread_trace__new());

	if (thread__priv(thread) == NULL)
		goto fail;

	ttrace = thread__priv(thread);
	++ttrace->nr_events;

	return ttrace;
fail:
	color_fprintf(fp, PERF_COLOR_RED,
		      "WARNING: not enough memory, dropping samples!\n");
	return NULL;
}